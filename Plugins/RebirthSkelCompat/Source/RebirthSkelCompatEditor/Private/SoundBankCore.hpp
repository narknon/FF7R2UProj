// SoundBankCore.hpp
// Create a Character System: new sound banks for FINAL FANTASY VII REBIRTH, made from WAV files.
//
//   WAV -> PCM -> HCA (CRI HCA 2.0, written by the encoder below, as the game's own voice banks have it: no cipher,
//   no ATH curve, 128 coded bands, resolutions 1-15) -> a SEAD sound bank ("sabf": sounds, sequences, tracks,
//   materials) -> the SQEXSEADSound package (zen, as the game cooks it) -> an IoStore container for ~mods.
//
// The HCA bit stream follows the format as the game's decoder reads it; every part of it the encoder writes (frame
// header, scalefactors in all their codings, the resolution each scalefactor and noise level give, the codebooks of
// every resolution, the quantizer steps, the IMDCT and its window) was checked against an independent decoder
// (ffmpeg's) by decoding test streams (tests/hca_tests).
//
// Portable C++17 without engine or OS types and without exceptions: the editor plugin and the command-line tool
// share it, and it is unit-tested off-target.
#pragma once

#include <algorithm>
#include <cctype>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace CacsSound
{
// ---------------------------------------------------------------------------------------
// Bytes
// ---------------------------------------------------------------------------------------
using Bytes = std::vector<uint8_t>;

inline void PutU8(Bytes& b, uint32_t v) { b.push_back(static_cast<uint8_t>(v)); }
inline void PutU16(Bytes& b, uint32_t v) { b.push_back(static_cast<uint8_t>(v)); b.push_back(static_cast<uint8_t>(v >> 8)); }
inline void PutU32(Bytes& b, uint32_t v) { for (int i = 0; i < 4; ++i) { b.push_back(static_cast<uint8_t>(v >> (8 * i))); } }
inline void PutU64(Bytes& b, uint64_t v) { for (int i = 0; i < 8; ++i) { b.push_back(static_cast<uint8_t>(v >> (8 * i))); } }
inline void PutI32(Bytes& b, int32_t v) { PutU32(b, static_cast<uint32_t>(v)); }
inline void PutF32(Bytes& b, float v) { uint32_t u; std::memcpy(&u, &v, 4); PutU32(b, u); }
inline void PutBE16(Bytes& b, uint32_t v) { b.push_back(static_cast<uint8_t>(v >> 8)); b.push_back(static_cast<uint8_t>(v)); }
inline void PutBE24(Bytes& b, uint32_t v) { b.push_back(static_cast<uint8_t>(v >> 16)); b.push_back(static_cast<uint8_t>(v >> 8)); b.push_back(static_cast<uint8_t>(v)); }
inline void PutBE32(Bytes& b, uint32_t v) { for (int i = 3; i >= 0; --i) { b.push_back(static_cast<uint8_t>(v >> (8 * i))); } }
inline void PutBytes(Bytes& b, const void* p, size_t n) { const auto* c = static_cast<const uint8_t*>(p); b.insert(b.end(), c, c + n); }
inline void PutText(Bytes& b, const char* s) { PutBytes(b, s, std::strlen(s)); }
inline void PadTo(Bytes& b, size_t align) { while (b.size() % align) { b.push_back(0); } }
inline void SetU16(Bytes& b, size_t at, uint32_t v) { b[at] = static_cast<uint8_t>(v); b[at + 1] = static_cast<uint8_t>(v >> 8); }
inline void SetU32(Bytes& b, size_t at, uint32_t v) { for (int i = 0; i < 4; ++i) { b[at + i] = static_cast<uint8_t>(v >> (8 * i)); } }
inline void SetU64(Bytes& b, size_t at, uint64_t v) { for (int i = 0; i < 8; ++i) { b[at + i] = static_cast<uint8_t>(v >> (8 * i)); } }
inline uint16_t GetU16(const uint8_t* p) { return static_cast<uint16_t>(p[0] | (p[1] << 8)); }
inline uint32_t GetU32(const uint8_t* p) { return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24); }
inline uint64_t GetU64(const uint8_t* p) { return static_cast<uint64_t>(GetU32(p)) | (static_cast<uint64_t>(GetU32(p + 4)) << 32); }

// ---------------------------------------------------------------------------------------
// PCM and WAV files
// ---------------------------------------------------------------------------------------
struct Pcm
{
    int Rate = 0;
    int Channels = 0;
    std::vector<float> Samples;   // interleaved, full scale -1..1
    size_t Frames() const { return Channels > 0 ? Samples.size() / static_cast<size_t>(Channels) : 0; }
    double Seconds() const { return Rate > 0 ? static_cast<double>(Frames()) / Rate : 0.0; }
    float Peak() const
    {
        float p = 0.0f;
        for (float s : Samples) { p = std::max(p, std::fabs(s)); }
        return p;
    }
};

// A RIFF WAVE file: PCM 8 (unsigned), 16, 24 or 32 bit, IEEE float 32 or 64 bit, WAVE_FORMAT_EXTENSIBLE of either.
inline bool ReadWav(const uint8_t* data, size_t size, Pcm& out, std::string& error)
{
    out = Pcm{};
    if (size < 12 || std::memcmp(data, "RIFF", 4) != 0 || std::memcmp(data + 8, "WAVE", 4) != 0)
    {
        error = "not a RIFF WAVE file";
        return false;
    }
    int format = 0, channels = 0, bits = 0, align = 0;
    uint32_t rate = 0;
    const uint8_t* samples = nullptr;
    size_t sampleBytes = 0;
    size_t at = 12;
    while (at + 8 <= size)
    {
        const uint8_t* chunk = data + at;
        const uint32_t length = GetU32(chunk + 4);
        const size_t body = at + 8;
        const size_t available = body <= size ? size - body : 0;
        if (std::memcmp(chunk, "fmt ", 4) == 0 && length >= 16 && available >= 16)
        {
            format = GetU16(chunk + 8);
            channels = GetU16(chunk + 10);
            rate = GetU32(chunk + 12);
            align = GetU16(chunk + 20);
            bits = GetU16(chunk + 22);
            if (format == 0xFFFE && length >= 40 && available >= 40) { format = GetU16(chunk + 32); }   // the sub-format GUID's first two bytes
        }
        else if (std::memcmp(chunk, "data", 4) == 0)
        {
            samples = data + body;
            sampleBytes = std::min<size_t>(length, available);
        }
        at = body + length + (length & 1);
    }
    if (!format || !samples)
    {
        error = "no fmt or data chunk";
        return false;
    }
    const bool isFloat = format == 3;
    if (!(format == 1 || isFloat) || channels < 1 || channels > 16 || rate < 4000 || rate > 192000 ||
        !(bits == 8 || bits == 16 || bits == 24 || bits == 32 || (isFloat && bits == 64)) || (isFloat && bits < 32))
    {
        error = "unsupported WAV format (format " + std::to_string(format) + ", " + std::to_string(bits) + " bit, " +
                std::to_string(channels) + " channels, " + std::to_string(rate) + " Hz): use PCM 8/16/24/32 bit or float 32/64 bit";
        return false;
    }
    const int bytesPer = bits / 8;
    if (align < bytesPer * channels) { align = bytesPer * channels; }
    const size_t frames = sampleBytes / static_cast<size_t>(align);
    out.Rate = static_cast<int>(rate);
    out.Channels = channels;
    out.Samples.resize(frames * static_cast<size_t>(channels));
    for (size_t f = 0; f < frames; ++f)
    {
        for (int c = 0; c < channels; ++c)
        {
            const uint8_t* p = samples + f * static_cast<size_t>(align) + static_cast<size_t>(c * bytesPer);
            float v = 0.0f;
            if (isFloat && bits == 32) { std::memcpy(&v, p, 4); }
            else if (isFloat) { double d; std::memcpy(&d, p, 8); v = static_cast<float>(d); }
            else if (bits == 8) { v = (static_cast<int>(p[0]) - 128) / 128.0f; }
            else if (bits == 16) { v = static_cast<int16_t>(GetU16(p)) / 32768.0f; }
            else if (bits == 24) { int32_t i = static_cast<int32_t>((p[0] << 8) | (p[1] << 16) | (static_cast<uint32_t>(p[2]) << 24)) >> 8; v = i / 8388608.0f; }
            else { v = static_cast<float>(static_cast<int32_t>(GetU32(p)) / 2147483648.0); }
            if (!std::isfinite(v)) { v = 0.0f; }
            out.Samples[f * static_cast<size_t>(channels) + static_cast<size_t>(c)] = std::clamp(v, -1.0f, 1.0f);
        }
    }
    return true;
}

// 16-bit PCM WAV bytes (for previews and tests).
inline Bytes WriteWav16(const Pcm& pcm)
{
    Bytes b;
    const uint32_t dataBytes = static_cast<uint32_t>(pcm.Samples.size() * 2);
    PutText(b, "RIFF"); PutU32(b, 36 + dataBytes); PutText(b, "WAVE");
    PutText(b, "fmt "); PutU32(b, 16); PutU16(b, 1); PutU16(b, static_cast<uint32_t>(pcm.Channels)); PutU32(b, static_cast<uint32_t>(pcm.Rate));
    PutU32(b, static_cast<uint32_t>(pcm.Rate * pcm.Channels * 2)); PutU16(b, static_cast<uint32_t>(pcm.Channels * 2)); PutU16(b, 16);
    PutText(b, "data"); PutU32(b, dataBytes);
    for (float s : pcm.Samples) { PutU16(b, static_cast<uint16_t>(static_cast<int16_t>(std::lround(std::clamp(s, -1.0f, 1.0f) * 32767.0f)))); }
    return b;
}

// The channels mixed down to `channels` (1: their average; the same count: as it is; 2 from 1: copied).
inline Pcm Mixdown(const Pcm& in, int channels)
{
    if (channels <= 0 || channels == in.Channels) { return in; }
    Pcm out;
    out.Rate = in.Rate;
    out.Channels = channels;
    const size_t frames = in.Frames();
    out.Samples.assign(frames * static_cast<size_t>(channels), 0.0f);
    for (size_t f = 0; f < frames; ++f)
    {
        for (int c = 0; c < channels; ++c)
        {
            float sum = 0.0f;
            int count = 0;
            for (int k = c; k < in.Channels; k += channels) { sum += in.Samples[f * static_cast<size_t>(in.Channels) + static_cast<size_t>(k)]; ++count; }
            if (count == 0) { sum = in.Samples[f * static_cast<size_t>(in.Channels) + static_cast<size_t>(c % in.Channels)]; count = 1; }
            out.Samples[f * static_cast<size_t>(channels) + static_cast<size_t>(c)] = sum / static_cast<float>(count);
        }
    }
    return out;
}

// Band-limited resampling (windowed sinc, Kaiser window, 32 zero crossings).
inline Pcm Resample(const Pcm& in, int rate)
{
    if (rate <= 0 || rate == in.Rate || in.Rate <= 0 || in.Frames() == 0) { return in; }
    Pcm out;
    out.Rate = rate;
    out.Channels = in.Channels;
    const double ratio = static_cast<double>(rate) / in.Rate;
    const size_t inFrames = in.Frames();
    const size_t outFrames = static_cast<size_t>(std::floor(inFrames * ratio));
    out.Samples.assign(outFrames * static_cast<size_t>(in.Channels), 0.0f);
    const double cutoff = std::min(1.0, ratio) * 0.97;
    const int half = 32;
    const double reach = half / cutoff;
    const double beta = 8.6;
    auto bessel0 = [](double x) {
        double sum = 1.0, term = 1.0;
        for (int k = 1; k < 40; ++k) { term *= (x / (2.0 * k)) * (x / (2.0 * k)); sum += term; }
        return sum;
    };
    const double norm = bessel0(beta);
    const double pi = 3.14159265358979323846;
    for (size_t o = 0; o < outFrames; ++o)
    {
        const double center = o / ratio;
        const long first = static_cast<long>(std::ceil(center - reach));
        const long last = static_cast<long>(std::floor(center + reach));
        for (int c = 0; c < in.Channels; ++c)
        {
            double sum = 0.0, weights = 0.0;
            for (long i = first; i <= last; ++i)
            {
                const double t = (i - center) * cutoff;
                const double r = (i - center) / reach;
                if (r <= -1.0 || r >= 1.0) { continue; }
                const double sinc = t == 0.0 ? 1.0 : std::sin(pi * t) / (pi * t);
                const double w = bessel0(beta * std::sqrt(1.0 - r * r)) / norm;
                const double k = sinc * w;
                weights += k;
                if (i >= 0 && static_cast<size_t>(i) < inFrames) { sum += k * in.Samples[static_cast<size_t>(i) * static_cast<size_t>(in.Channels) + static_cast<size_t>(c)]; }
            }
            out.Samples[o * static_cast<size_t>(in.Channels) + static_cast<size_t>(c)] = static_cast<float>(weights > 0.0 ? sum / weights : 0.0);
        }
    }
    return out;
}

// Scales every sample by `gain` (clipped to full scale).
inline void Gain(Pcm& pcm, float gain)
{
    for (float& s : pcm.Samples) { s = std::clamp(s * gain, -1.0f, 1.0f); }
}

// ---------------------------------------------------------------------------------------
// HCA 2.0 encoder
// ---------------------------------------------------------------------------------------
namespace Hca
{
constexpr int SubframeSamples = 128;
constexpr int Subframes = 8;
constexpr int FrameSamples = SubframeSamples * Subframes;   // 1024
constexpr int Delay = 128;            // the samples the decoder's first subframe lacks (the game's own files: 128)
constexpr int MinResolution = 1;      // as the game's files (and its decoder's noise filling stays off)
constexpr int MaxResolution = 15;
constexpr int Bands = 128;            // total = base band count; no intensity stereo, no high-frequency reconstruction

// Bits of the code of resolution r's widest code; the codebooks of resolutions 1-7 (index r * 16 + the next MaxBit[r]
// bits: how many of them the code takes and its value).
constexpr uint8_t MaxBit[16] = {0, 2, 3, 3, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12};
constexpr uint8_t ReadBit[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};
constexpr int8_t ReadVal[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, -1, -1, 2, -2, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, -1, 2, -2, 3, -3, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, -1, -1, 2, 2, -2, -2, 3, 3, -3, -3, 4, -4,
    0, 0, 1, 1, -1, -1, 2, 2, -2, -2, 3, -3, 4, -4, 5, -5,
    0, 0, 1, 1, -1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6,
    0, 0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7,
};
// The resolution of a curve position (noise level + 1 - 5/2 scalefactor; below 0: 15, above 65: 0).
constexpr uint8_t Invert[66] = {
    14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12,
    12, 12, 11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 10, 10, 9,
    9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 7, 6, 6, 5, 4,
    4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
    1, 1,
};
// The IMDCT window's first half (the second mirrors it), as the decoder's synthesis has it (measured: tests/hca_tests).
constexpr float WindowHalf[128] = {
    6.905338463e-04f, 1.976230099e-03f, 3.673860941e-03f, 5.724237742e-03f, 8.096701610e-03f, 1.077319916e-02f, 1.374249406e-02f, 1.699789197e-02f,
    2.053530224e-02f, 2.435291120e-02f, 2.845050640e-02f, 3.282909797e-02f, 3.749059738e-02f, 4.243790378e-02f, 4.767439677e-02f, 5.320428444e-02f,
    5.903210451e-02f, 6.516287551e-02f, 7.160202134e-02f, 7.835516065e-02f, 8.542852702e-02f, 9.282801304e-02f, 1.005600037e-01f, 1.086310176e-01f,
    1.170480359e-01f, 1.258170627e-01f, 1.349440353e-01f, 1.444370016e-01f, 1.543000114e-01f, 1.645389293e-01f, 1.751609730e-01f, 1.861689468e-01f,
    1.975689976e-01f, 2.093629996e-01f, 2.215549637e-01f, 2.341449281e-01f, 2.471359433e-01f, 2.605259650e-01f, 2.743128589e-01f, 2.884930126e-01f,
    3.030619528e-01f, 3.180119119e-01f, 3.333330405e-01f, 3.490150477e-01f, 3.650440951e-01f, 3.814029620e-01f, 3.980728989e-01f, 4.150339557e-01f,
    4.322600075e-01f, 4.497250236e-01f, 4.673999829e-01f, 4.852509716e-01f, 5.032448901e-01f, 5.213438282e-01f, 5.395089301e-01f, 5.576979929e-01f,
    5.758689996e-01f, 5.939781137e-01f, 6.119807305e-01f, 6.298310944e-01f, 6.474861676e-01f, 6.649001810e-01f, 6.820311150e-01f, 6.988379904e-01f,
    7.152799894e-01f, 7.313231558e-01f, 7.469322254e-01f, 7.620772026e-01f, 7.767321240e-01f, 7.908726734e-01f, 8.044811995e-01f, 8.175419838e-01f,
    8.300439438e-01f, 8.419798776e-01f, 8.533467131e-01f, 8.641438425e-01f, 8.743749165e-01f, 8.840459581e-01f, 8.931670634e-01f, 9.017490149e-01f,
    9.098059220e-01f, 9.173537852e-01f, 9.244088817e-01f, 9.309902301e-01f, 9.371171199e-01f, 9.428091451e-01f, 9.480867175e-01f, 9.529708562e-01f,
    9.574820007e-01f, 9.616405022e-01f, 9.654668413e-01f, 9.689808179e-01f, 9.722017037e-01f, 9.751478852e-01f, 9.778379899e-01f, 9.802889835e-01f,
    9.825177470e-01f, 9.845398080e-01f, 9.863705900e-01f, 9.880240415e-01f, 9.895139982e-01f, 9.908532219e-01f, 9.920534596e-01f, 9.931262545e-01f,
    9.940821405e-01f, 9.949309954e-01f, 9.956821581e-01f, 9.963443013e-01f, 9.969255082e-01f, 9.974332812e-01f, 9.978746413e-01f, 9.982560847e-01f,
    9.985836490e-01f, 9.988629295e-01f, 9.990991064e-01f, 9.992969804e-01f, 9.994609799e-01f, 9.995952024e-01f, 9.997034239e-01f, 9.997891284e-01f,
    9.998555254e-01f, 9.999055675e-01f, 9.999419674e-01f, 9.999672212e-01f, 9.999836164e-01f, 9.999932514e-01f, 9.999980473e-01f, 9.999997616e-01f,
};

inline uint16_t Crc16(const uint8_t* p, size_t n)
{
    static const std::array<uint16_t, 256> table = [] {
        std::array<uint16_t, 256> t{};
        for (uint32_t i = 0; i < 256; ++i)
        {
            uint32_t c = i << 8;
            for (int b = 0; b < 8; ++b) { c = (c & 0x8000) ? ((c << 1) ^ 0x8005) : (c << 1); }
            t[i] = static_cast<uint16_t>(c);
        }
        return t;
    }();
    uint16_t c = 0;
    for (size_t i = 0; i < n; ++i) { c = static_cast<uint16_t>((c << 8) ^ table[((c >> 8) ^ p[i]) & 0xFF]); }
    return c;
}

inline double Scale(int sf) { return std::sqrt(128.0) * std::exp2((sf - 63) * 53.0 / 128.0); }
inline double Step(int r) { return r <= 0 ? 0.0 : (r <= 7 ? 2.0 / (2 * r + 1) : 2.0 / ((1 << (r - 3)) - 1)); }
inline int Levels(int r) { return r <= 0 ? 0 : (r <= 7 ? r : (1 << (r - 4)) - 1); }

// The resolution the decoder gives a coefficient (frame noise level, evaluation boundary, its scalefactor and index).
// `noise` >= 1 whenever `boundary` > 0 (the decoder's packed level is unsigned).
inline int ResolutionOf(int sf, int noise, int boundary, int index)
{
    if (sf <= 0) { return 0; }
    const int packed = (noise << 8) - boundary;
    const int level = (packed + index) >> 8;
    const int curve = level + 1 - ((5 * sf) >> 1);
    int r = curve < 0 ? 15 : (curve <= 65 ? Invert[curve] : 0);
    return std::clamp(r, MinResolution, MaxResolution);
}

// The code of quantized value q at resolution r: its bits and value.
struct Code
{
    uint32_t Value = 0;
    int Bits = 0;
};

inline const std::array<std::array<Code, 15>, 8>& SmallCodes()
{
    static const std::array<std::array<Code, 15>, 8> codes = [] {
        std::array<std::array<Code, 15>, 8> t{};
        for (int r = 1; r <= 7; ++r)
        {
            const int width = MaxBit[r];
            for (int code = 0; code < (1 << width); ++code)
            {
                const int index = (r << 4) + code;
                const int used = ReadBit[index];
                Code& c = t[static_cast<size_t>(r)][static_cast<size_t>(ReadVal[index] + 7)];
                if (c.Bits == 0) { c = Code{static_cast<uint32_t>(code >> (width - used)), used}; }
            }
        }
        return t;
    }();
    return codes;
}

inline Code CodeOf(int r, int q)
{
    if (r <= 0) { return Code{}; }
    if (r <= 7) { return SmallCodes()[static_cast<size_t>(r)][static_cast<size_t>(q + 7)]; }
    const int width = MaxBit[r];
    if (q == 0) { return Code{0, width - 1}; }   // a zero has no sign bit
    return Code{(static_cast<uint32_t>(std::abs(q)) << 1) | (q < 0 ? 1u : 0u), width};
}

struct BitWriter
{
    uint8_t* Data = nullptr;
    size_t Capacity = 0;   // bits
    size_t At = 0;
    bool Overflow = false;
    void Put(uint32_t value, int bits)
    {
        if (At + static_cast<size_t>(bits) > Capacity) { Overflow = true; return; }
        for (int i = bits - 1; i >= 0; --i)
        {
            if ((value >> i) & 1u) { Data[At >> 3] |= static_cast<uint8_t>(0x80u >> (At & 7)); }
            ++At;
        }
    }
};

struct Info
{
    int Channels = 0;
    int Rate = 0;
    int FrameBytes = 0;
    int Frames = 0;
    int Delay = 0;
    int Padding = 0;
    size_t Samples = 0;        // per channel
    double Seconds = 0.0;
    int HeaderBytes = 0;
    double MeanNoise = 0.0;    // the frames' mean noise level (higher: coarser)
};

// The frame size for a bit rate per channel (the game's voice banks: 341 bytes for 32 kHz mono, 85 kbit/s).
inline int FrameBytesFor(int rate, int channels, double kbpsPerChannel)
{
    const double bytes = kbpsPerChannel * 1000.0 / 8.0 * FrameSamples / std::max(1, rate) * std::max(1, channels);
    return std::clamp(static_cast<int>(std::lround(bytes)), 64 * std::max(1, channels), 0xFFFF);
}

// The 96-byte header: version 2.0, fmt, comp, ciph (none), pad, its CRC.
inline Bytes Header(const Info& info)
{
    Bytes h;
    PutText(h, "HCA");
    PutU8(h, 0);
    PutBE16(h, 0x0200);
    PutBE16(h, 96);
    PutText(h, "fmt"); PutU8(h, 0);
    PutU8(h, static_cast<uint32_t>(info.Channels));
    PutBE24(h, static_cast<uint32_t>(info.Rate));
    PutBE32(h, static_cast<uint32_t>(info.Frames));
    PutBE16(h, static_cast<uint32_t>(info.Delay));
    PutBE16(h, static_cast<uint32_t>(info.Padding));
    PutText(h, "comp");
    PutBE16(h, static_cast<uint32_t>(info.FrameBytes));
    PutU8(h, MinResolution);
    PutU8(h, MaxResolution);
    PutU8(h, 1);                                   // track count
    PutU8(h, info.Channels == 1 ? 1 : 0);          // channel config (as the game's mono files)
    PutU8(h, Bands);                               // total band count
    PutU8(h, Bands);                               // base band count
    PutU8(h, 0);                                   // stereo band count: every channel coded on its own
    PutU8(h, 0);                                   // bands per HFR group: no high-frequency reconstruction
    PutU8(h, 0);                                   // M/S stereo
    PutU8(h, 0);
    PutText(h, "ciph"); PutBE16(h, 0);             // no cipher
    PutText(h, "pad"); PutU8(h, 0);
    while (h.size() < 94) { h.push_back(0); }
    const uint16_t crc = Crc16(h.data(), h.size());
    PutBE16(h, crc);
    return h;
}

// Reads an HCA header (fmt and comp chunks; names may have their high bits set) into `info`.
inline bool ParseHeader(const uint8_t* data, size_t size, Info& info)
{
    if (size < 8 || (data[0] & 0x7F) != 'H' || (data[1] & 0x7F) != 'C' || (data[2] & 0x7F) != 'A') { return false; }
    const int dataOffset = (data[6] << 8) | data[7];
    if (dataOffset < 8 || static_cast<size_t>(dataOffset) > size) { return false; }
    info = Info{};
    info.HeaderBytes = dataOffset;
    size_t p = 8;
    bool fmt = false, comp = false;
    while (p + 4 <= static_cast<size_t>(dataOffset))
    {
        char tag[5] = {static_cast<char>(data[p] & 0x7F), static_cast<char>(data[p + 1] & 0x7F), static_cast<char>(data[p + 2] & 0x7F), static_cast<char>(data[p + 3] & 0x7F), 0};
        if (std::strcmp(tag, "fmt") == 0 && p + 16 <= size)
        {
            info.Channels = data[p + 4];
            info.Rate = (data[p + 5] << 16) | (data[p + 6] << 8) | data[p + 7];
            info.Frames = static_cast<int>((static_cast<uint32_t>(data[p + 8]) << 24) | (data[p + 9] << 16) | (data[p + 10] << 8) | data[p + 11]);
            info.Delay = (data[p + 12] << 8) | data[p + 13];
            info.Padding = (data[p + 14] << 8) | data[p + 15];
            fmt = true;
            p += 16;
        }
        else if ((std::strcmp(tag, "comp") == 0 || std::strcmp(tag, "dec") == 0) && p + 6 <= size)
        {
            info.FrameBytes = (data[p + 4] << 8) | data[p + 5];
            comp = true;
            p += std::strcmp(tag, "comp") == 0 ? 16 : 12;
        }
        else if (std::strcmp(tag, "vbr") == 0) { p += 8; }
        else if (std::strcmp(tag, "ath") == 0) { p += 6; }
        else if (std::strcmp(tag, "loop") == 0) { p += 16; }
        else if (std::strcmp(tag, "ciph") == 0) { p += 6; }
        else if (std::strcmp(tag, "rva") == 0) { p += 8; }
        else if (std::strcmp(tag, "comm") == 0 && p + 5 <= size) { p += 5 + data[p + 4]; }
        else { break; }   // pad
    }
    if (!fmt || !comp || info.Rate <= 0) { return false; }
    const long long samples = static_cast<long long>(info.Frames) * FrameSamples - info.Delay - info.Padding;
    info.Samples = samples > 0 ? static_cast<size_t>(samples) : 0;
    info.Seconds = static_cast<double>(info.Samples) / info.Rate;
    return true;
}

class Encoder
{
public:
    Encoder()
    {
        const double pi = 3.14159265358979323846;
        Basis.resize(SubframeSamples * 2 * SubframeSamples);
        for (int k = 0; k < SubframeSamples; ++k)
        {
            for (int n = 0; n < 2 * SubframeSamples; ++n)
            {
                const double w = WindowHalf[n < SubframeSamples ? n : 2 * SubframeSamples - 1 - n];
                Basis[static_cast<size_t>(k * 2 * SubframeSamples + n)] =
                    -0.125 * w * std::cos(pi / SubframeSamples * (n + 0.5 + SubframeSamples / 2) * (k + 0.5));
            }
        }
    }

    // `frameBytes`: the size of every frame (FrameBytesFor). Empty when the PCM cannot be encoded.
    Bytes Encode(const Pcm& pcm, int frameBytes, Info* infoOut = nullptr, std::string* error = nullptr) const
    {
        Info info;
        info.Channels = pcm.Channels;
        info.Rate = pcm.Rate;
        info.FrameBytes = frameBytes;
        info.Delay = Delay;
        info.Samples = pcm.Frames();
        info.Seconds = pcm.Seconds();
        if (pcm.Channels < 1 || pcm.Channels > 16 || pcm.Rate < 4000 || pcm.Rate > 0xFFFFFF || frameBytes < 16 || frameBytes > 0xFFFF)
        {
            if (error) { *error = "cannot encode " + std::to_string(pcm.Channels) + " channels at " + std::to_string(pcm.Rate) + " Hz in frames of " + std::to_string(frameBytes) + " bytes"; }
            return {};
        }
        const size_t total = static_cast<size_t>(Delay) + info.Samples;
        info.Frames = static_cast<int>(total == 0 ? 1 : (total - 1) / FrameSamples + 1);
        info.Padding = static_cast<int>(static_cast<size_t>(info.Frames) * FrameSamples - total);
        // the signal, each channel, at its place in the stream (after the delay), with room for the last window
        const int channels = pcm.Channels;
        const size_t span = static_cast<size_t>(info.Frames) * FrameSamples + 2 * SubframeSamples;
        std::vector<std::vector<double>> signal(static_cast<size_t>(channels), std::vector<double>(span, 0.0));
        for (size_t f = 0; f < info.Samples; ++f)
        {
            for (int c = 0; c < channels; ++c) { signal[static_cast<size_t>(c)][Delay + f] = pcm.Samples[f * static_cast<size_t>(channels) + static_cast<size_t>(c)]; }
        }
        Bytes out = Header(info);
        info.HeaderBytes = static_cast<int>(out.size());
        out.reserve(out.size() + static_cast<size_t>(info.Frames) * static_cast<size_t>(frameBytes));
        double noiseSum = 0.0;
        std::vector<Frame> chans(static_cast<size_t>(channels));
        for (int frame = 0; frame < info.Frames; ++frame)
        {
            for (int c = 0; c < channels; ++c)
            {
                Frame& ch = chans[static_cast<size_t>(c)];
                for (int s = 0; s < Subframes; ++s)
                {
                    const double* x = signal[static_cast<size_t>(c)].data() + static_cast<size_t>((frame * Subframes + s) * SubframeSamples);
                    for (int k = 0; k < SubframeSamples; ++k)
                    {
                        const double* b = Basis.data() + static_cast<size_t>(k * 2 * SubframeSamples);
                        double sum = 0.0;
                        for (int n = 0; n < 2 * SubframeSamples; ++n) { sum += b[n] * x[n]; }
                        ch.X[static_cast<size_t>(s)][static_cast<size_t>(k)] = sum;
                    }
                }
                Prepare(ch);
            }
            int noise = 0, boundary = 0;
            if (!Fit(chans, frameBytes, noise, boundary))
            {
                if (error) { *error = "frame " + std::to_string(frame) + " does not fit in " + std::to_string(frameBytes) + " bytes"; }
                return {};
            }
            DropBelowFloor(chans, noise, boundary);
            // A coefficient whose eight values all quantize to zero at its resolution costs bits for nothing: it is
            // left out (scalefactor 0) and the bits it freed go to the rest (a finer noise level), a few times over.
            for (int pass = 0; pass < 4; ++pass)
            {
                int dropped = 0;
                for (Frame& ch : chans)
                {
                    bool changed = false;
                    for (int i = 0; i < Bands; ++i)
                    {
                        const int sf = ch.Sf[static_cast<size_t>(i)];
                        const int r = ResolutionOf(sf, noise, boundary, i);
                        if (r == 0) { continue; }
                        bool zero = true;
                        for (int s = 0; s < Subframes && zero; ++s) { zero = Quantize(ch.X[static_cast<size_t>(s)][static_cast<size_t>(i)], sf, r) == 0; }
                        if (zero)
                        {
                            ch.Sf[static_cast<size_t>(i)] = 0;
                            changed = true;
                            ++dropped;
                        }
                    }
                    if (changed) { Costs(ch); }
                }
                if (dropped == 0 || !Fit(chans, frameBytes, noise, boundary)) { break; }
                DropBelowFloor(chans, noise, boundary);
            }
            noiseSum += noise;
            const size_t at = out.size();
            out.resize(at + static_cast<size_t>(frameBytes), 0);
            BitWriter w{out.data() + at, static_cast<size_t>(frameBytes - 2) * 8};
            w.Put(0xFFFF, 16);
            w.Put(static_cast<uint32_t>(noise), 9);
            w.Put(static_cast<uint32_t>(boundary), 7);
            for (const Frame& ch : chans) { WriteScalefactors(w, ch); }
            for (int s = 0; s < Subframes; ++s)
            {
                for (const Frame& ch : chans)
                {
                    for (int i = 0; i < Bands; ++i)
                    {
                        const int r = ResolutionOf(ch.Sf[static_cast<size_t>(i)], noise, boundary, i);
                        if (r == 0) { continue; }
                        const int q = Quantize(ch.X[static_cast<size_t>(s)][static_cast<size_t>(i)], ch.Sf[static_cast<size_t>(i)], r);
                        const Code code = CodeOf(r, q);
                        w.Put(code.Value, code.Bits);
                    }
                }
            }
            if (w.Overflow)
            {
                if (error) { *error = "frame " + std::to_string(frame) + " overflowed"; }
                return {};
            }
            const uint16_t crc = Crc16(out.data() + at, static_cast<size_t>(frameBytes - 2));
            out[at + static_cast<size_t>(frameBytes) - 2] = static_cast<uint8_t>(crc >> 8);
            out[at + static_cast<size_t>(frameBytes) - 1] = static_cast<uint8_t>(crc);
        }
        info.MeanNoise = info.Frames ? noiseSum / info.Frames : 0.0;
        if (infoOut) { *infoOut = info; }
        return out;
    }

private:
    struct Frame
    {
        std::array<std::array<double, Bands>, Subframes> X{};
        std::array<int, Bands> Sf{};
        int SfBits = 0, DeltaBits = 0;
        std::array<std::array<int, 16>, Bands> Cost{};   // bits of each coefficient's 8 values at each resolution
    };

    std::vector<double> Basis;   // 128 x 256: the decoder's synthesis functions (orthonormal), analysis is their transpose

    static int Quantize(double x, int sf, int r)
    {
        const double step = Scale(sf) * Step(r);
        const int L = Levels(r);
        const long q = std::lround(x / step);
        return static_cast<int>(std::clamp<long>(q, -L, L));
    }

    // Scalefactors: the smallest whose scale holds the coefficient's peak in the frame (0: nothing to code).
    static void Prepare(Frame& ch)
    {
        for (int i = 0; i < Bands; ++i)
        {
            double peak = 0.0;
            for (int s = 0; s < Subframes; ++s) { peak = std::max(peak, std::fabs(ch.X[static_cast<size_t>(s)][static_cast<size_t>(i)])); }
            int sf = 0;
            if (peak > Scale(1) * 0.5)
            {
                sf = static_cast<int>(std::ceil(std::log2(peak / std::sqrt(128.0)) * 128.0 / 53.0 + 63.0 - 1e-9));
                sf = std::clamp(sf, 1, 63);
                while (sf > 1 && Scale(sf - 1) >= peak) { --sf; }
                while (sf < 63 && Scale(sf) < peak) { ++sf; }
            }
            ch.Sf[static_cast<size_t>(i)] = sf;
        }
        Costs(ch);
    }

    // The bits of each coefficient's 8 values at each resolution, and the scalefactors' cheapest coding: none (all
    // zero), 6 bits each, or deltas of 1-5 bits.
    static void Costs(Frame& ch)
    {
        for (int i = 0; i < Bands; ++i)
        {
            const int sf = ch.Sf[static_cast<size_t>(i)];
            for (int r = 1; r <= MaxResolution; ++r)
            {
                int bits = 0;
                for (int s = 0; s < Subframes; ++s) { bits += CodeOf(r, sf ? Quantize(ch.X[static_cast<size_t>(s)][static_cast<size_t>(i)], sf, r) : 0).Bits; }
                ch.Cost[static_cast<size_t>(i)][static_cast<size_t>(r)] = bits;
            }
        }
        ch.SfBits = ScalefactorBits(ch.Sf, &ch.DeltaBits);
    }

    static void WriteScalefactors(BitWriter& w, const Frame& ch)
    {
        w.Put(static_cast<uint32_t>(ch.DeltaBits), 3);
        if (ch.DeltaBits == 0) { return; }
        if (ch.DeltaBits >= 6)
        {
            for (int sf : ch.Sf) { w.Put(static_cast<uint32_t>(sf), 6); }
            return;
        }
        const int escape = (1 << ch.DeltaBits) - 1;
        w.Put(static_cast<uint32_t>(ch.Sf[0]), 6);
        for (int i = 1; i < Bands; ++i)
        {
            const int d = ch.Sf[static_cast<size_t>(i)] - ch.Sf[static_cast<size_t>(i - 1)] + (escape >> 1);
            if (d >= 0 && d < escape) { w.Put(static_cast<uint32_t>(d), ch.DeltaBits); }
            else
            {
                w.Put(static_cast<uint32_t>(escape), ch.DeltaBits);
                w.Put(static_cast<uint32_t>(ch.Sf[static_cast<size_t>(i)]), 6);
            }
        }
    }

    // Below the noise floor: the decoder's curve position is past its table (a 0-resolution coefficient, were the
    // minimum resolution 0); the encoder leaves such a coefficient out (scalefactor 0) rather than spend bits on it.
    static bool BelowFloor(int sf, int noise, int boundary, int index)
    {
        const int level = ((noise << 8) - boundary + index) >> 8;
        return level + 1 - ((5 * sf) >> 1) > 65;
    }

    static int ScalefactorBits(const std::array<int, Bands>& sf, int* deltaBits = nullptr)
    {
        bool any = false;
        for (int v : sf) { any = any || v != 0; }
        if (!any) { if (deltaBits) { *deltaBits = 0; } return 3; }
        int best = 3 + 6 * Bands, bestDb = 6;
        for (int db = 1; db <= 5; ++db)
        {
            const int escape = (1 << db) - 1;
            int bits = 3 + 6;
            for (int i = 1; i < Bands; ++i)
            {
                const int d = sf[static_cast<size_t>(i)] - sf[static_cast<size_t>(i - 1)] + (escape >> 1);
                bits += db + ((d >= 0 && d < escape) ? 0 : 6);
            }
            if (bits < best) { best = bits; bestDb = db; }
        }
        if (deltaBits) { *deltaBits = bestDb; }
        return best;
    }

    static int Bits(const std::vector<Frame>& chans, int noise, int boundary)
    {
        int bits = 16 + 9 + 7 + 16;   // sync, noise level, boundary, CRC
        std::array<int, Bands> kept{};
        for (const Frame& ch : chans)
        {
            for (int i = 0; i < Bands; ++i)
            {
                const int sf = ch.Sf[static_cast<size_t>(i)];
                const bool keep = sf > 0 && !BelowFloor(sf, noise, boundary, i);
                kept[static_cast<size_t>(i)] = keep ? sf : 0;
                if (keep) { bits += ch.Cost[static_cast<size_t>(i)][static_cast<size_t>(ResolutionOf(sf, noise, boundary, i))]; }
            }
            bits += ScalefactorBits(kept);
        }
        return bits;
    }

    // Leaves out the coefficients below the noise floor of (noise, boundary).
    static void DropBelowFloor(std::vector<Frame>& chans, int noise, int boundary)
    {
        for (Frame& ch : chans)
        {
            bool changed = false;
            for (int i = 0; i < Bands; ++i)
            {
                const int sf = ch.Sf[static_cast<size_t>(i)];
                if (sf > 0 && BelowFloor(sf, noise, boundary, i)) { ch.Sf[static_cast<size_t>(i)] = 0; changed = true; }
            }
            if (changed) { Costs(ch); }
        }
    }

    // The finest noise level (and then the widest finer band below the evaluation boundary) whose frame fits;
    // if even the coarsest does not, the highest coefficients are left out until it does.
    static bool Fit(std::vector<Frame>& chans, int frameBytes, int& noise, int& boundary)
    {
        const int budget = frameBytes * 8;
        for (;;)
        {
            if (Bits(chans, 511, 0) <= budget)
            {
                int lo = 0, hi = 511;   // the smallest that fits
                while (lo < hi)
                {
                    const int mid = (lo + hi) / 2;
                    if (Bits(chans, mid, 0) <= budget) { hi = mid; } else { lo = mid + 1; }
                }
                noise = lo;
                boundary = 0;
                if (noise >= 1)
                {
                    int b0 = 0, b1 = 127;   // the largest boundary that still fits
                    while (b0 < b1)
                    {
                        const int mid = (b0 + b1 + 1) / 2;
                        if (Bits(chans, noise, mid) <= budget) { b0 = mid; } else { b1 = mid - 1; }
                    }
                    boundary = b0;
                }
                return true;
            }
            // drop the highest coded coefficient of the channel coding the most
            Frame* widest = nullptr;
            int top = -1;
            for (Frame& ch : chans)
            {
                for (int i = Bands - 1; i >= 0; --i)
                {
                    if (ch.Sf[static_cast<size_t>(i)] != 0)
                    {
                        if (i > top) { top = i; widest = &ch; }
                        break;
                    }
                }
            }
            if (!widest) { return false; }
            widest->Sf[static_cast<size_t>(top)] = 0;
            Costs(*widest);
        }
    }

};
} // namespace Hca

// ---------------------------------------------------------------------------------------
// CityHash64 (the version the engine's package ids, name hashes and object hashes use) and SHA-1
// ---------------------------------------------------------------------------------------
namespace Hash
{
constexpr uint64_t K0 = 0xc3a5c85c97cb3127ULL, K1 = 0xb492b66fbe98f273ULL, K2 = 0x9ae16a3b2f90404fULL;
inline uint64_t F64(const uint8_t* s) { return GetU64(s); }
inline uint64_t F32(const uint8_t* s) { return GetU32(s); }
inline uint64_t Rot(uint64_t v, int sh) { return sh == 0 ? v : ((v >> sh) | (v << (64 - sh))); }
inline uint64_t ShiftMix(uint64_t v) { return v ^ (v >> 47); }
inline uint64_t Swap64(uint64_t v)
{
    uint64_t r = 0;
    for (int i = 0; i < 8; ++i) { r = (r << 8) | ((v >> (8 * i)) & 0xff); }
    return r;
}
inline uint64_t Len16(uint64_t u, uint64_t v, uint64_t mul = 0x9ddfea08eb382d69ULL)
{
    uint64_t a = (u ^ v) * mul;
    a ^= a >> 47;
    uint64_t b = (v ^ a) * mul;
    b ^= b >> 47;
    return b * mul;
}
inline uint64_t Len0to16(const uint8_t* s, size_t n)
{
    if (n >= 8)
    {
        const uint64_t mul = K2 + n * 2;
        const uint64_t a = F64(s) + K2, b = F64(s + n - 8);
        const uint64_t c = Rot(b, 37) * mul + a, d = (Rot(a, 25) + b) * mul;
        return Len16(c, d, mul);
    }
    if (n >= 4)
    {
        const uint64_t mul = K2 + n * 2;
        const uint64_t a = F32(s);
        return Len16(n + (a << 3), F32(s + n - 4), mul);
    }
    if (n > 0)
    {
        const uint8_t a = s[0], b = s[n >> 1], c = s[n - 1];
        const uint32_t y = static_cast<uint32_t>(a) + (static_cast<uint32_t>(b) << 8);
        const uint32_t z = static_cast<uint32_t>(n) + (static_cast<uint32_t>(c) << 2);
        return ShiftMix(y * K2 ^ z * K0) * K2;
    }
    return K2;
}
inline uint64_t Len17to32(const uint8_t* s, size_t n)
{
    const uint64_t mul = K2 + n * 2;
    const uint64_t a = F64(s) * K1, b = F64(s + 8), c = F64(s + n - 8) * mul, d = F64(s + n - 16) * K2;
    return Len16(Rot(a + b, 43) + Rot(c, 30) + d, a + Rot(b + K2, 18) + c, mul);
}
inline void WeakHash(uint64_t w, uint64_t x, uint64_t y, uint64_t z, uint64_t a, uint64_t b, uint64_t& outA, uint64_t& outB)
{
    a += w;
    b = Rot(b + a + z, 21);
    const uint64_t c = a;
    a += x;
    a += y;
    b += Rot(a, 44);
    outA = a + z;
    outB = b + c;
}
inline void WeakHash(const uint8_t* s, uint64_t a, uint64_t b, uint64_t& outA, uint64_t& outB)
{
    WeakHash(F64(s), F64(s + 8), F64(s + 16), F64(s + 24), a, b, outA, outB);
}
inline uint64_t Len33to64(const uint8_t* s, size_t n)
{
    const uint64_t mul = K2 + n * 2;
    uint64_t a = F64(s) * K2;
    uint64_t b = F64(s + 8);
    const uint64_t c = F64(s + n - 24), d = F64(s + n - 32);
    const uint64_t e = F64(s + 16) * K2, f = F64(s + 24) * 9, g = F64(s + n - 8), h = F64(s + n - 16) * mul;
    const uint64_t u = Rot(a + g, 43) + (Rot(b, 30) + c) * 9;
    const uint64_t v = ((a + g) ^ d) + f + 1;
    const uint64_t w = Swap64((u + v) * mul) + h;
    const uint64_t x = Rot(e + f, 42) + c;
    const uint64_t y = (Swap64((v + w) * mul) + g) * mul;
    const uint64_t z = e + f + c;
    a = Swap64((x + z) * mul + y) + b;
    b = ShiftMix((z + a) * mul + d + h) * mul;
    return b + x;
}
inline uint64_t City64(const uint8_t* s, size_t n)
{
    if (n <= 32) { return n <= 16 ? Len0to16(s, n) : Len17to32(s, n); }
    if (n <= 64) { return Len33to64(s, n); }
    uint64_t x = F64(s + n - 40);
    uint64_t y = F64(s + n - 16) + F64(s + n - 56);
    uint64_t z = Len16(F64(s + n - 48) + n, F64(s + n - 24));
    uint64_t v0, v1, w0, w1;
    WeakHash(s + n - 64, n, z, v0, v1);
    WeakHash(s + n - 32, y + K1, x, w0, w1);
    x = x * K1 + F64(s);
    size_t len = (n - 1) & ~static_cast<size_t>(63);
    const uint8_t* p = s;
    do
    {
        x = Rot(x + y + v0 + F64(p + 8), 37) * K1;
        y = Rot(y + v1 + F64(p + 48), 42) * K1;
        x ^= w1;
        y += v0 + F64(p + 40);
        z = Rot(z + w0, 33) * K1;
        WeakHash(p, v1 * K1, x + w0, v0, v1);
        WeakHash(p + 32, z + w1, y + F64(p + 16), w0, w1);
        std::swap(z, x);
        p += 64;
        len -= 64;
    } while (len != 0);
    return Len16(Len16(v0, w0) + ShiftMix(y) * K1 + z, Len16(v1, w1) + x);
}

// SHA-1 (the container's chunk hashes).
inline std::array<uint8_t, 20> Sha1(const uint8_t* data, size_t size)
{
    uint32_t h[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    auto rol = [](uint32_t v, int n) { return (v << n) | (v >> (32 - n)); };
    std::vector<uint8_t> m(data, data + size);
    const uint64_t bits = static_cast<uint64_t>(size) * 8;
    m.push_back(0x80);
    while (m.size() % 64 != 56) { m.push_back(0); }
    for (int i = 7; i >= 0; --i) { m.push_back(static_cast<uint8_t>(bits >> (8 * i))); }
    for (size_t chunk = 0; chunk < m.size(); chunk += 64)
    {
        uint32_t w[80];
        for (int i = 0; i < 16; ++i)
        {
            w[i] = (static_cast<uint32_t>(m[chunk + 4 * i]) << 24) | (static_cast<uint32_t>(m[chunk + 4 * i + 1]) << 16) |
                   (static_cast<uint32_t>(m[chunk + 4 * i + 2]) << 8) | static_cast<uint32_t>(m[chunk + 4 * i + 3]);
        }
        for (int i = 16; i < 80; ++i) { w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1); }
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        for (int i = 0; i < 80; ++i)
        {
            uint32_t f, k;
            if (i < 20) { f = (b & c) | (~b & d); k = 0x5A827999; }
            else if (i < 40) { f = b ^ c ^ d; k = 0x6ED9EBA1; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else { f = b ^ c ^ d; k = 0xCA62C1D6; }
            const uint32_t t = rol(a, 5) + f + e + k + w[i];
            e = d; d = c; c = rol(b, 30); b = a; a = t;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e;
    }
    std::array<uint8_t, 20> out{};
    for (int i = 0; i < 5; ++i) { for (int j = 0; j < 4; ++j) { out[static_cast<size_t>(4 * i + j)] = static_cast<uint8_t>(h[i] >> (24 - 8 * j)); } }
    return out;
}
} // namespace Hash

// ---------------------------------------------------------------------------------------
// Engine ids: package ids, object (import) hashes, name hashes, FName number suffixes
// ---------------------------------------------------------------------------------------
namespace Ids
{
inline std::string Lower(std::string s)
{
    for (char& c : s) { if (c >= 'A' && c <= 'Z') { c = static_cast<char>(c - 'A' + 'a'); } }
    return s;
}
inline Bytes Utf16(const std::string& ascii)
{
    Bytes b;
    for (char c : ascii) { b.push_back(static_cast<uint8_t>(c)); b.push_back(0); }
    return b;
}
// FPackageId of a package name (/Game/...): CityHash64 of its lower-case UTF-16.
inline uint64_t PackageId(const std::string& package)
{
    const Bytes u = Utf16(Lower(package));
    return Hash::City64(u.data(), u.size());
}
// The hash of an object path (/Game/Pkg.Object, /Script/Module.Class), as FPackageObjectIndex has it.
inline uint64_t ObjectHash(const std::string& path)
{
    std::string s = Lower(path);
    for (char& c : s) { if (c == '.' || c == ':') { c = '/'; } }
    const Bytes u = Utf16(s);
    return Hash::City64(u.data(), u.size()) & ~(3ULL << 62);
}
inline uint64_t ScriptImport(const std::string& path) { return (1ULL << 62) | ObjectHash(path); }
inline uint64_t PackageImport(const std::string& path) { return (2ULL << 62) | ObjectHash(path); }
constexpr uint64_t Null = 0xFFFFFFFFFFFFFFFFULL;
inline uint64_t NameHash(const std::string& name)
{
    const std::string l = Lower(name);
    return Hash::City64(reinterpret_cast<const uint8_t*>(l.data()), l.size());
}
// An FName's text split the engine's way: "bt021_001_sep_0" -> ("bt021_001_sep", 1); "Sep_wall_end_01" stays whole
// (a number with a leading zero is part of the name).
inline void SplitName(const std::string& text, std::string& base, uint32_t& number)
{
    base = text;
    number = 0;
    const size_t us = text.rfind('_');
    if (us == std::string::npos || us + 1 >= text.size() || us == 0) { return; }
    const std::string digits = text.substr(us + 1);
    if (digits.size() > 10 || !std::all_of(digits.begin(), digits.end(), [](char c) { return c >= '0' && c <= '9'; })) { return; }
    if (digits.size() > 1 && digits[0] == '0') { return; }
    const unsigned long long v = std::stoull(digits);
    if (v >= 0x7FFFFFFFULL) { return; }
    base = text.substr(0, us);
    number = static_cast<uint32_t>(v + 1);
}
inline bool NameLess(const std::string& a, const std::string& b) { return Lower(a) < Lower(b); }
} // namespace Ids

// ---------------------------------------------------------------------------------------
// SEAD sound banks ("sabf"): one sound -> one sequence -> one track -> one material each, laid out as the game's
// voice banks are (the entries' fixed parts are the game's own: a voice's 3D curves and categories).
// ---------------------------------------------------------------------------------------
namespace Sead
{
constexpr uint8_t SoundHead[112] = {
    0x14, 0xff, 0x70, 0x00, 0x01, 0x01, 0x11, 0x80, 0x00, 0x00, 0x00, 0x00, 0xb6, 0xb3, 0xe4, 0x3e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xf0, 0x41,
    0x00, 0x00, 0x01, 0x13, 0x81, 0x95, 0x83, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f,
    0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f,
};
constexpr uint8_t SequenceEntry[496] = {
    0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0xd0, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x10, 0x20, 0x00, 0x05, 0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1c, 0x45,
    0xff, 0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7a, 0x65, 0x72, 0x6f, 0x6f, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xab, 0xaa, 0x2a, 0x3e, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7c, 0x1f, 0xed, 0x3e, 0x6e, 0x0c, 0x62, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xab, 0xaa, 0x2a, 0x3f, 0x8e, 0x52, 0x46, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x3f, 0x58, 0x4f, 0x1e, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x10, 0x20, 0x00, 0x05, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1c, 0x45,
    0xff, 0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7a, 0x65, 0x72, 0x6f, 0x6f, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x3f, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xab, 0xaa, 0x2a, 0x3e, 0xfe, 0xff, 0x3f, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0xcc, 0xcc, 0x3e, 0xfe, 0xff, 0x3f, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0xcc, 0x4c, 0x3f, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x3f, 0xfa, 0xff, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x10, 0x20, 0x00, 0x04, 0x00, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1c, 0x45,
    0xff, 0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7a, 0x65, 0x72, 0x6f, 0x6f, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfa, 0xff, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xab, 0xaa, 0x2a, 0x3e, 0xfa, 0xff, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xcd, 0xcc, 0xcc, 0x3e, 0xfa, 0xff, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x3f, 0xfe, 0xff, 0x3f, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x04, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x95, 0x83, 0x3e,
    0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
constexpr uint8_t TrackEntry[144] = {
    0x02, 0x01, 0x10, 0x00, 0x00, 0x00, 0x0e, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
    0x02, 0x04, 0x03, 0x14, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x02, 0x04, 0x04, 0x14, 0x00, 0x00, 0x80, 0x3f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f,
    0x01, 0x04, 0x0f, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x10, 0x14, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x04, 0x12, 0x14, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

struct Sound
{
    std::string Name;        // the cue name, e.g. bt021_001_001_sep_0
    Bytes Hca;               // a whole HCA stream (Hca::Encoder::Encode)
    Hca::Info Info;
    float Volume = 0.4467f;  // the sound's own volume (the game's US voice lines: 0.4467, -7 dB)
    uint8_t Category = 0x11; // the entry's bytes 6 and 0x23 (the game's: 0x11 and 0x13 for most of a voice bank)
    uint8_t Bus = 0x13;
    int Id = -1;             // its sequence, track and material id (-1: its index; the ids are a permutation of the indices)
    float Length = -1.0f;    // the length the bank gives it (s; below 0: its HCA stream's, samples / rate)
    double Seconds() const { return Length >= 0.0f ? Length : (Info.Rate > 0 ? static_cast<double>(Info.Samples) / Info.Rate : 0.0); }
};

struct Bank
{
    std::string Name;        // at most 31 characters
    uint16_t Id = 0;         // the bank id (the tracks name it)
    std::vector<Sound> Sounds;
};

// A bank id for a new bank: from its name, clear of the game's own ids where we know them (any 16-bit id but 0).
inline uint16_t IdFor(const std::string& name)
{
    const uint64_t h = Ids::NameHash("CreateACharacterSystem.Bank." + name);
    uint16_t id = static_cast<uint16_t>(h ^ (h >> 16) ^ (h >> 32) ^ (h >> 48));
    if (id == 0) { id = 1; }
    return id;
}

inline bool ValidName(const std::string& name)
{
    if (name.empty() || name.size() > 31) { return false; }
    return std::all_of(name.begin(), name.end(), [](char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-'; });
}

inline Bytes Write(const Bank& bank, std::string* error = nullptr)
{
    if (!ValidName(bank.Name))
    {
        if (error) { *error = "a bank name is 1-31 letters, digits, '_' or '-': " + bank.Name; }
        return {};
    }
    const size_t count = bank.Sounds.size();
    if (count == 0 || count > 0xFFFF)
    {
        if (error) { *error = "a bank needs 1-65535 sounds"; }
        return {};
    }
    for (const Sound& s : bank.Sounds)
    {
        if (!ValidName(s.Name) && !(s.Name.size() <= 63 && ValidName(s.Name.substr(0, 31))))
        {
            if (error) { *error = "a sound name is letters, digits, '_' or '-' (at most 63): " + s.Name; }
            return {};
        }
        if (s.Hca.size() < 96 || std::memcmp(s.Hca.data(), "HCA", 3) != 0)
        {
            if (error) { *error = "sound " + s.Name + " has no HCA stream"; }
            return {};
        }
    }
    std::vector<size_t> ids(count), byId(count, count);
    for (size_t i = 0; i < count; ++i)
    {
        const int id = bank.Sounds[i].Id;
        ids[i] = id < 0 ? i : static_cast<size_t>(id);
        if (ids[i] >= count || byId[ids[i]] != count)
        {
            if (error) { *error = "the sounds' ids are not a permutation of 0.." + std::to_string(count - 1); }
            return {};
        }
        byId[ids[i]] = i;
    }
    Bytes b;
    // header: magic, version 2, 4 chunks, the name, the chunk table
    PutText(b, "sabf");
    PutU8(b, 2); PutU8(b, 0); PutU16(b, 0x10);
    PutU8(b, 4); PutU8(b, static_cast<uint32_t>(bank.Name.size())); PutU16(b, bank.Id);
    PutU32(b, 0);                                   // total size (below)
    PutText(b, bank.Name.c_str());
    while (b.size() < 0x30) { b.push_back(0); }
    const char* tags[4] = {"snd ", "seq ", "trk ", "mtrl"};
    const size_t table = b.size();
    for (const char* tag : tags) { PutText(b, tag); PutU16(b, 0); PutU16(b, 0x10); PutU32(b, 0); PutU32(b, 0); }
    auto chunk = [&](int which, uint8_t version) {
        const size_t at = b.size();
        SetU32(b, table + static_cast<size_t>(which) * 16 + 8, static_cast<uint32_t>(at));
        PutU8(b, version); PutU8(b, 0); PutU16(b, 0x10); PutU16(b, static_cast<uint32_t>(count));
        while (b.size() < at + 0x10) { b.push_back(0); }
        const size_t offsets = b.size();
        for (size_t i = 0; i < count; ++i) { PutU32(b, 0); }
        PadTo(b, 16);
        return std::make_pair(at, offsets);
    };
    // sounds
    {
        const auto [at, offsets] = chunk(0, 1);
        for (size_t i = 0; i < count; ++i)
        {
            const Sound& s = bank.Sounds[i];
            const size_t e = b.size();
            SetU32(b, offsets + 4 * i, static_cast<uint32_t>(e - at));
            PutBytes(b, SoundHead, sizeof(SoundHead));
            const size_t nameBytes = ((s.Name.size() + 1 + 15) / 16) * 16;
            const uint32_t trailer = static_cast<uint32_t>(sizeof(SoundHead) + nameBytes);
            b[e + 6] = s.Category;
            SetU32(b, e + 0x08, static_cast<uint32_t>(i));
            float vol = s.Volume;
            uint32_t vbits; std::memcpy(&vbits, &vol, 4); SetU32(b, e + 0x0C, vbits);
            SetU16(b, e + 0x1A, trailer);
            b[e + 0x23] = s.Bus;
            float len = static_cast<float>(s.Seconds());
            uint32_t lbits; std::memcpy(&lbits, &len, 4); SetU32(b, e + 0x24, lbits);
            SetU16(b, e + 0x46, trailer);
            SetU32(b, e + 0x4C, trailer);
            PutText(b, s.Name.c_str());
            while (b.size() < e + trailer) { b.push_back(0); }
            PutU8(b, 1); PutU8(b, 0); PutU16(b, 0x10);
            PutU16(b, static_cast<uint32_t>(i));     // its sequence's index and id
            PutU16(b, static_cast<uint32_t>(ids[i]));
            PutU32(b, 0); PutU32(b, 0);
        }
    }
    // sequences: the game's voice curves, then the play command of the sound's track and its length
    {
        const auto [at, offsets] = chunk(1, 0);
        for (size_t i = 0; i < count; ++i)
        {
            const Sound& s = bank.Sounds[i];
            const size_t e = b.size();
            SetU32(b, offsets + 4 * i, static_cast<uint32_t>(e - at));
            PutBytes(b, SequenceEntry, sizeof(SequenceEntry));
            SetU16(b, e + 4, static_cast<uint32_t>(ids[i]));
            const size_t play = e + 0x1D0;
            SetU16(b, play + 4, static_cast<uint32_t>(i));
            SetU16(b, play + 10, static_cast<uint32_t>(ids[i]));
            float len = static_cast<float>(s.Seconds());
            uint32_t lbits; std::memcpy(&lbits, &len, 4); SetU32(b, play + 12, lbits);
        }
    }
    // tracks: each plays its material from this bank
    {
        const auto [at, offsets] = chunk(2, 0);
        for (size_t i = 0; i < count; ++i)
        {
            const size_t e = b.size();
            SetU32(b, offsets + 4 * i, static_cast<uint32_t>(e - at));
            PutBytes(b, TrackEntry, sizeof(TrackEntry));
            SetU16(b, e + 4, static_cast<uint32_t>(ids[i]));
            SetU16(b, e + 6, bank.Id);
            SetU16(b, e + 8, static_cast<uint32_t>(ids[i]));     // its material: the one at the place of its id
            SetU16(b, e + 10, static_cast<uint32_t>(ids[i]));
        }
    }
    // materials: the HCA streams (a 16-byte SEAD header, the HCA header, the frames)
    {
        const auto [at, offsets] = chunk(3, 0);
        for (size_t i = 0; i < count; ++i)
        {
            const Sound& s = bank.Sounds[byId[i]];
            PadTo(b, 16);
            const size_t e = b.size();
            SetU32(b, offsets + 4 * i, static_cast<uint32_t>(e - at));
            const size_t header = static_cast<size_t>(s.Info.HeaderBytes ? s.Info.HeaderBytes : 96);
            const size_t stream = s.Hca.size() - header;
            PutU8(b, 1); PutU8(b, 0); PutU16(b, 0x20);
            PutU8(b, static_cast<uint32_t>(s.Info.Channels)); PutU8(b, 7); PutU16(b, static_cast<uint32_t>(i));
            PutU32(b, static_cast<uint32_t>(s.Info.Rate));
            PutU32(b, 0); PutU32(b, 0);                              // no loop
            PutU32(b, static_cast<uint32_t>(16 + header));           // extra data: SEAD's HCA header and the HCA header
            PutU32(b, static_cast<uint32_t>(stream));
            PutU32(b, static_cast<uint32_t>(i));                     // material id
            PutU8(b, 1); PutU8(b, 0x10); PutU16(b, static_cast<uint32_t>(header));
            PutU32(b, static_cast<uint32_t>(s.Info.FrameBytes));
            PutU16(b, 0); PutU16(b, static_cast<uint32_t>(s.Info.Delay));
            PutU32(b, 0);
            PutBytes(b, s.Hca.data(), s.Hca.size());
        }
        PadTo(b, 16);
    }
    SetU32(b, 0x0C, static_cast<uint32_t>(b.size()));
    return b;
}
} // namespace Sead

// ---------------------------------------------------------------------------------------
// Zen packages (UE 4.26 IoStore, as the game cooks them): the name map, imports, one export
// ---------------------------------------------------------------------------------------
namespace Zen
{
class Names
{
public:
    // Adds a name (its text without an FName number) and returns nothing; Index() finds it once Sort() ran.
    void Add(const std::string& n)
    {
        if (std::find(List.begin(), List.end(), n) == List.end()) { List.push_back(n); }
    }
    void Sort() { std::stable_sort(List.begin(), List.end(), Ids::NameLess); }
    void Append(const std::string& n) { List.push_back(n); }   // after the sorted ones (a localized package's source name)
    // Adds an FName's text the engine's way: "VO_A_01" is "VO_A_01" (a leading zero), "VO_A_1" is "VO_A" with a number.
    void AddText(const std::string& text)
    {
        std::string base;
        uint32_t number = 0;
        Ids::SplitName(text, base, number);
        Add(base);
    }
    // An FName's FMappedName (index in the low half, number in the high half) for text that may carry a number suffix.
    uint64_t Mapped(const std::string& text) const
    {
        uint32_t index = 0, number = 0;
        Of(text, index, number);
        return static_cast<uint64_t>(index) | (static_cast<uint64_t>(number) << 32);
    }
    uint32_t Index(const std::string& n) const
    {
        for (size_t i = 0; i < List.size(); ++i) { if (List[i] == n) { return static_cast<uint32_t>(i); } }
        return 0xFFFFFFFFu;
    }
    // An FName's (index, number) for text that may carry a number suffix.
    void Of(const std::string& text, uint32_t& index, uint32_t& number) const
    {
        std::string base;
        Ids::SplitName(text, base, number);
        index = Index(base);
    }
    Bytes Blob() const
    {
        Bytes b;
        for (const std::string& n : List) { PutU8(b, static_cast<uint32_t>(n.size() >> 8)); PutU8(b, static_cast<uint32_t>(n.size() & 0xFF)); PutText(b, n.c_str()); }
        return b;
    }
    Bytes Hashes() const
    {
        Bytes b;
        PutU64(b, 0x00000000C1640000ULL);
        for (const std::string& n : List) { PutU64(b, Ids::NameHash(n)); }
        return b;
    }
    std::vector<std::string> List;
};

// The unversioned property header for the schema positions present (ascending), every value non-zero.
inline Bytes UnversionedHeader(const std::vector<int>& present)
{
    Bytes b;
    int next = 0;
    size_t i = 0;
    while (i < present.size())
    {
        int skip = present[i] - next;
        while (skip > 127) { PutU16(b, 127); skip -= 127; }   // (a fragment of skips only)
        size_t run = 1;
        while (i + run < present.size() && present[i + run] == present[i + run - 1] + 1 && run < 127) { ++run; }
        const bool last = i + run == present.size();
        PutU16(b, static_cast<uint32_t>(skip) | (last ? 0x100u : 0u) | (static_cast<uint32_t>(run) << 9));
        next = present[i] + static_cast<int>(run);
        i += run;
    }
    if (present.empty()) { PutU16(b, 0x100); }
    return b;
}

struct Import
{
    uint64_t Index = Ids::Null;   // FPackageObjectIndex (script or package import; Null for a package entry)
};

struct ExportSpec
{
    std::string ObjectName;
    uint64_t Class = Ids::Null, Super = Ids::Null, Template = Ids::Null, GlobalImport = Ids::Null;
    uint32_t Flags = 0xB;   // RF_Public | RF_Standalone | RF_Transactional
};

// One package with one export: the summary, names, hashes, imports, export map, one bundle, the graph (imported
// packages, each with one arc into the bundle), header padded to 16, the export's data.
// `name`, `source`: the package's FMappedNames (Names::Mapped: a name whose text ends in _<number> is its base and number).
inline Bytes Package(uint64_t name, uint64_t source, const Names& names, const std::vector<uint64_t>& imports,
                     const ExportSpec& ex, const std::vector<uint64_t>& importedPackages, const Bytes& exportData)
{
    const Bytes blob = names.Blob(), hashes = names.Hashes();
    Bytes b(64, 0);
    const size_t nmOff = b.size();
    PutBytes(b, blob.data(), blob.size());
    PadTo(b, 8);
    const size_t nhOff = b.size();
    PutBytes(b, hashes.data(), hashes.size());
    const size_t impOff = b.size();
    for (uint64_t v : imports) { PutU64(b, v); }
    const size_t expOff = b.size();
    // export map entry (offsets set below)
    PutU64(b, 0); PutU64(b, exportData.size());
    uint32_t objIndex = 0, objNumber = 0;
    names.Of(ex.ObjectName, objIndex, objNumber);
    PutU32(b, objIndex); PutU32(b, objNumber);
    PutU64(b, Ids::Null); PutU64(b, ex.Class); PutU64(b, ex.Super); PutU64(b, ex.Template); PutU64(b, ex.GlobalImport);
    PutU32(b, ex.Flags); PutU8(b, 0); PutU8(b, 0); PutU8(b, 0); PutU8(b, 0);
    const size_t ebOff = b.size();
    PutU32(b, 0); PutU32(b, 2);              // bundle header: first entry 0, 2 entries
    PutU32(b, 0); PutU32(b, 0);              // export 0: create
    PutU32(b, 0); PutU32(b, 1);              // export 0: serialize
    const size_t graphOff = b.size();
    std::vector<uint64_t> sorted = importedPackages;
    std::sort(sorted.begin(), sorted.end());
    PutI32(b, static_cast<int32_t>(sorted.size()));
    for (uint64_t pid : sorted) { PutU64(b, pid); PutI32(b, 1); PutI32(b, 0); PutI32(b, 0); }
    PadTo(b, 16);
    const size_t headerEnd = b.size();
    SetU64(b, expOff, headerEnd);           // cooked serial offset (= the cooked header size below)
    // summary
    SetU64(b, 0, name);
    SetU64(b, 8, source);
    SetU32(b, 16, 0x80802200u);             // the game's package flags for cooked unversioned assets
    SetU32(b, 20, static_cast<uint32_t>(headerEnd));
    SetU32(b, 24, static_cast<uint32_t>(nmOff));
    SetU32(b, 28, static_cast<uint32_t>(blob.size()));
    SetU32(b, 32, static_cast<uint32_t>(nhOff));
    SetU32(b, 36, static_cast<uint32_t>(hashes.size()));
    SetU32(b, 40, static_cast<uint32_t>(impOff));
    SetU32(b, 44, static_cast<uint32_t>(expOff));
    SetU32(b, 48, static_cast<uint32_t>(ebOff));
    SetU32(b, 52, static_cast<uint32_t>(graphOff));
    SetU32(b, 56, static_cast<uint32_t>(headerEnd - graphOff));
    SetU32(b, 60, 0);
    PutBytes(b, exportData.data(), exportData.size());
    return b;
}
} // namespace Zen

// ---------------------------------------------------------------------------------------
// The SQEXSEADSound package of a bank
// ---------------------------------------------------------------------------------------
namespace BankPackage
{
struct Spec
{
    std::string Package;       // /Game/Sound/Voice/JP/Character/Player/VO_PC0010_13_YoungSephiroth (its asset: the last part)
    std::string Source;        // a localized package's source package (JP), else empty
    std::string AliasSetting;  // the SQEXSEADSoundAliasNameSetting asset its sound names go through, e.g.
                               // /Game/Sound/Config/AliasSetting/VO_PC0010_00_Sephiroth (empty: none)
    std::string Attenuation = "/Game/Sound/Config/Attenuation/player";   // a SoundAttenuation asset (empty: none)
    float Duration = 10000.0f;  // SoundBase's Duration, as the game's banks have it
};

inline std::string LastPart(const std::string& path)
{
    const size_t s = path.rfind('/');
    return s == std::string::npos ? path : path.substr(s + 1);
}
inline std::string ObjectPath(const std::string& package) { return package + "." + LastPart(package); }

// The cooked SQEXSEADSound export and its package. `sab`: Sead::Write's bytes.
inline Bytes Write(const Spec& spec, const Sead::Bank& bank, const Bytes& sab, std::string* error = nullptr)
{
    const std::string asset = LastPart(spec.Package);
    if (spec.Package.rfind("/Game/", 0) != 0 || asset.empty())
    {
        if (error) { *error = "the package must be under /Game/: " + spec.Package; }
        return {};
    }
    const std::string source = spec.Source.empty() ? spec.Package : spec.Source;
    // names: the cooker's (sorted), the source name of a localized package after them
    Zen::Names names;
    for (const char* n : {"/Script/CoreUObject", "/Script/Engine", "/Script/SQEXSEAD", "Class", "Default__SQEXSEADSound", "Duration", "FloatProperty",
                          "IntProperty", "MapProperty", "NameProperty", "None", "ObjectProperty", "Package", "SoundIndex", "SoundNameIndexTable",
                          "SQEXSEADSound", "StructProperty", "VoicedSectionAdjustmentTime"})
    {
        names.Add(n);
    }
    // (names ending in _<number> are their base and a number, as the engine stores them: a bank or package named
    // VO_A_1 is "VO_A" number 2, and the engine finds it by that FName)
    names.AddText(spec.Package);
    names.AddText(asset);
    if (!spec.AliasSetting.empty())
    {
        names.AddText(spec.AliasSetting);
        names.AddText(LastPart(spec.AliasSetting));
        names.Add("SoundNameAliasSetting");
        names.Add("SQEXSEADSoundAliasNameSetting");
    }
    if (!spec.Attenuation.empty())
    {
        names.AddText(spec.Attenuation);
        names.AddText(LastPart(spec.Attenuation));
        names.Add("AttenuationSettings");
        names.Add("SoundAttenuation");
    }
    for (const Sead::Sound& s : bank.Sounds)
    {
        std::string base;
        uint32_t number = 0;
        Ids::SplitName(s.Name, base, number);
        names.Add(base);
    }
    names.Sort();
    if (source != spec.Package)
    {
        std::string base;
        uint32_t number = 0;
        Ids::SplitName(source, base, number);
        if (names.Index(base) == 0xFFFFFFFFu) { names.Append(base); }
    }
    // imports, in the cooker's order: the class, the asset packages (null in a zen package), the script package, the
    // attenuation, the class default object, the alias setting
    std::vector<uint64_t> imports;
    imports.push_back(Ids::ScriptImport("/Script/SQEXSEAD.SQEXSEADSound"));
    if (!spec.AliasSetting.empty()) { imports.push_back(Ids::Null); }
    if (!spec.Attenuation.empty()) { imports.push_back(Ids::Null); }
    imports.push_back(Ids::ScriptImport("/Script/SQEXSEAD"));
    int32_t attenuationIndex = 0, aliasIndex = 0;
    if (!spec.Attenuation.empty())
    {
        imports.push_back(Ids::PackageImport(ObjectPath(spec.Attenuation)));
        attenuationIndex = -static_cast<int32_t>(imports.size());
    }
    imports.push_back(Ids::ScriptImport("/Script/SQEXSEAD.Default__SQEXSEADSound"));
    if (!spec.AliasSetting.empty())
    {
        imports.push_back(Ids::PackageImport(ObjectPath(spec.AliasSetting)));
        aliasIndex = -static_cast<int32_t>(imports.size());
    }
    // the export: unversioned properties (SQEXSEADSound's own first, then SoundWave's, then SoundBase's):
    // 13 SoundNameIndexTable, 14 SoundNameAliasSetting, 54 Duration, 58 AttenuationSettings
    std::vector<int> present{13};
    if (aliasIndex) { present.push_back(14); }
    present.push_back(54);
    if (attenuationIndex) { present.push_back(58); }
    Bytes e = Zen::UnversionedHeader(present);
    PutI32(e, 0);                                              // the map: none to remove
    PutI32(e, static_cast<int32_t>(bank.Sounds.size()));
    for (size_t i = 0; i < bank.Sounds.size(); ++i)
    {
        const Sead::Sound& s = bank.Sounds[i];
        uint32_t index = 0, number = 0;
        names.Of(s.Name, index, number);
        PutU32(e, index); PutU32(e, number);
        // FSQEXSEADSoundIndexInfo: SoundIndex, Duration, VoicedSectionAdjustmentTime (zeros left out)
        const float seconds = static_cast<float>(s.Seconds());
        const bool zeroIndex = i == 0, zeroSeconds = seconds == 0.0f;
        PutU16(e, 0x0780);                                     // 3 values, last fragment, some zero
        PutU8(e, (zeroIndex ? 1u : 0u) | (zeroSeconds ? 2u : 0u) | 4u);
        if (!zeroIndex) { PutI32(e, static_cast<int32_t>(i)); }
        if (!zeroSeconds) { PutF32(e, seconds); }
    }
    if (aliasIndex) { PutI32(e, aliasIndex); }
    PutF32(e, spec.Duration);
    if (attenuationIndex) { PutI32(e, attenuationIndex); }
    // the native part: the SEAD data block (16-aligned in the package), then SoundWave's tail
    PutU32(e, 0);
    PutU32(e, static_cast<uint32_t>(sab.size() + 16));
    PutU8(e, 0); PutU8(e, 0); PutU8(e, 1); PutU8(e, 0); PutU8(e, 0x10); PutU8(e, 0);
    const size_t padAt = e.size();
    PutU16(e, 0);
    // the package header's size is known once the names and imports are: lay the package out to find the pad
    std::vector<uint64_t> importedPackages;
    if (!spec.Attenuation.empty()) { importedPackages.push_back(Ids::PackageId(spec.Attenuation)); }
    if (!spec.AliasSetting.empty()) { importedPackages.push_back(Ids::PackageId(spec.AliasSetting)); }
    Zen::ExportSpec ex;
    ex.ObjectName = asset;
    ex.Class = Ids::ScriptImport("/Script/SQEXSEAD.SQEXSEADSound");
    ex.Template = Ids::ScriptImport("/Script/SQEXSEAD.Default__SQEXSEADSound");
    ex.GlobalImport = Ids::PackageImport(ObjectPath(source));
    const uint64_t nameMapped = names.Mapped(spec.Package);
    const uint64_t sourceMapped = names.Mapped(source);
    if ((nameMapped & 0xFFFFFFFFu) == 0xFFFFFFFFu || (sourceMapped & 0xFFFFFFFFu) == 0xFFFFFFFFu)
    {
        if (error) { *error = "the package's name is not in its name map"; }
        return {};
    }
    const size_t headerEnd = Zen::Package(nameMapped, sourceMapped, names, imports, ex, importedPackages, Bytes{}).size();
    size_t pad = 0;
    while ((headerEnd + e.size() + pad) % 16) { ++pad; }
    SetU16(e, padAt, static_cast<uint32_t>(pad));
    for (size_t i = 0; i < pad; ++i) { e.push_back(0); }
    PutU8(e, 0x21);
    for (int i = 0; i < 7; ++i) { e.push_back(0); }
    PutU32(e, static_cast<uint32_t>(sab.size()));
    PutU32(e, static_cast<uint32_t>(sab.size()));
    PutBytes(e, sab.data(), sab.size());
    // SoundWave's cooked tail: no bulk data, the compressed data guid (ours, from the package), the flags the game has
    PutU32(e, 0); PutU32(e, 0); PutU32(e, 0); PutU32(e, 1); PutU32(e, 0);
    const uint64_t g1 = Ids::NameHash("CreateACharacterSystem.Guid." + spec.Package), g2 = Ids::NameHash(spec.Package + ".Guid");
    PutU64(e, g1); PutU64(e, g2);
    PutU32(e, 1); PutU32(e, 0); PutU32(e, 0);
    Bytes pkg = Zen::Package(nameMapped, sourceMapped, names, imports, ex, importedPackages, e);
    if (pkg.size() != headerEnd + e.size())
    {
        if (error) { *error = "package layout changed between passes"; }
        return {};
    }
    (void)bank;
    return pkg;
}
} // namespace BankPackage

// ---------------------------------------------------------------------------------------
// IoStore containers for ~mods: the container header, .utoc, .ucas (uncompressed 64 KB blocks) and the .pak
// ---------------------------------------------------------------------------------------
namespace Container
{
constexpr uint32_t Block = 65536;

struct Package
{
    std::string Path;        // /Game/...
    Bytes Data;              // the zen package
    uint32_t ExportCount = 1, BundleCount = 1;
    uint64_t SizeFlags = 0;  // high bits of the store entry's size (4ULL << 60: exports aligned to 16, as SEAD banks)
    uint32_t LoadOrder = 1001;
    std::vector<uint64_t> ImportedPackages;
};

inline Bytes FString(const std::string& s)
{
    Bytes b;
    PutI32(b, static_cast<int32_t>(s.size() + 1));
    PutText(b, s.c_str());
    PutU8(b, 0);
    return b;
}

inline uint64_t ContainerId(const std::string& name) { return Ids::PackageId(name); }

// A localized package: its source (the JP voice package, which everything imports) and the variants the game loads in
// its place for the other voice languages (in the game's order: DE, FR, US; the game's records list those three).
struct Localized
{
    uint64_t Source = 0;
    std::vector<uint64_t> Variants;
};

inline Bytes Header(uint64_t cid, const std::vector<Package>& packages, const std::vector<Localized>& localized = {})
{
    Bytes out;
    PutU64(out, cid);
    PutU32(out, static_cast<uint32_t>(packages.size()));
    PutU32(out, static_cast<uint32_t>(localized.size()));   // localization records
    PutI32(out, 0);                                  // names
    PutI32(out, 8); PutU64(out, 0xC1640000ULL);      // name hashes: the algorithm id only
    PutI32(out, static_cast<int32_t>(packages.size()));
    for (const Package& p : packages) { PutU64(out, Ids::PackageId(p.Path)); }
    // the records (the game's layout: 04, the variant count, 02, 04, a u32 (0x0b with three variants, 0 with two), the
    // variants' package ids); a source package's store entry gives its record's offset in place of 0xFFFFFFFF
    Bytes records;
    std::vector<std::pair<uint64_t, uint32_t>> recordAt;
    for (const Localized& l : localized)
    {
        recordAt.emplace_back(l.Source, static_cast<uint32_t>(records.size()));
        PutU8(records, 4); PutU8(records, static_cast<uint32_t>(l.Variants.size())); PutU8(records, 2); PutU8(records, 4);
        PutU32(records, l.Variants.size() == 3 ? 0x0Bu : 0u);
        for (uint64_t v : l.Variants) { PutU64(records, v); }
    }
    Bytes entries, tail;
    const size_t n = packages.size();
    for (size_t i = 0; i < n; ++i)
    {
        const Package& p = packages[i];
        const size_t field = i * 32 + 24;
        uint32_t off = 0;
        if (!p.ImportedPackages.empty())
        {
            const size_t dataPos = n * 32 + tail.size();
            off = static_cast<uint32_t>(dataPos - field);
            for (uint64_t v : p.ImportedPackages) { PutU64(tail, v); }
        }
        uint32_t record = 0xFFFFFFFFu;
        const uint64_t pid = Ids::PackageId(p.Path);
        for (const auto& [source, at] : recordAt) { if (source == pid) { record = at; } }
        PutU64(entries, static_cast<uint64_t>(p.Data.size()) | p.SizeFlags);
        PutI32(entries, static_cast<int32_t>(p.ExportCount));
        PutI32(entries, static_cast<int32_t>(p.BundleCount));
        PutU32(entries, p.LoadOrder);
        PutU32(entries, record);
        PutU32(entries, static_cast<uint32_t>(p.ImportedPackages.size()));
        PutU32(entries, off);
    }
    PutI32(out, static_cast<int32_t>(entries.size() + tail.size()));
    PutBytes(out, entries.data(), entries.size());
    PutBytes(out, tail.data(), tail.size());
    PutI32(out, 0);                                  // culture package map
    PutI32(out, 0);                                  // package redirects
    if (!localized.empty())
    {
        PutI32(out, static_cast<int32_t>(records.size()));
        PutBytes(out, records.data(), records.size());
    }
    return out;
}

struct Chunk
{
    uint64_t Id = 0;
    uint8_t Type = 2;
    const Bytes* Data = nullptr;
    std::string File;        // relative to the mount point, e.g. Sound/Voice/JP/Character/Player/VO_X.uasset ("": none)
};

inline Bytes DirectoryIndex(const std::string& mount, const std::vector<std::pair<std::string, uint32_t>>& files)
{
    std::vector<std::string> strings;
    auto sidx = [&](const std::string& s) {
        for (size_t i = 0; i < strings.size(); ++i) { if (strings[i] == s) { return static_cast<uint32_t>(i); } }
        strings.push_back(s);
        return static_cast<uint32_t>(strings.size() - 1);
    };
    struct Dir { uint32_t Name, FirstChild, NextSibling, FirstFile; };
    struct File { uint32_t Name, Next, Chunk; };
    const uint32_t none = 0xFFFFFFFFu;
    std::vector<Dir> dirs{{none, none, none, none}};
    std::vector<File> fents;
    auto child = [&](uint32_t d, const std::string& name) {
        const uint32_t ni = sidx(name);
        uint32_t c = dirs[d].FirstChild, last = none;
        while (c != none)
        {
            if (dirs[c].Name == ni) { return c; }
            last = c;
            c = dirs[c].NextSibling;
        }
        dirs.push_back({ni, none, none, none});
        const uint32_t made = static_cast<uint32_t>(dirs.size() - 1);
        if (last == none) { dirs[d].FirstChild = made; } else { dirs[last].NextSibling = made; }
        return made;
    };
    for (const auto& [path, chunk] : files)
    {
        uint32_t d = 0;
        size_t start = 0;
        for (;;)
        {
            const size_t slash = path.find('/', start);
            if (slash == std::string::npos) { break; }
            d = child(d, path.substr(start, slash - start));
            start = slash + 1;
        }
        fents.push_back({sidx(path.substr(start)), none, chunk});
        const uint32_t fi = static_cast<uint32_t>(fents.size() - 1);
        uint32_t f = dirs[d].FirstFile;
        if (f == none) { dirs[d].FirstFile = fi; }
        else
        {
            while (fents[f].Next != none) { f = fents[f].Next; }
            fents[f].Next = fi;
        }
    }
    Bytes out = FString(mount);
    PutI32(out, static_cast<int32_t>(dirs.size()));
    for (const Dir& d : dirs) { PutU32(out, d.Name); PutU32(out, d.FirstChild); PutU32(out, d.NextSibling); PutU32(out, d.FirstFile); }
    PutI32(out, static_cast<int32_t>(fents.size()));
    for (const File& f : fents) { PutU32(out, f.Name); PutU32(out, f.Next); PutU32(out, f.Chunk); }
    PutI32(out, static_cast<int32_t>(strings.size()));
    for (const std::string& s : strings) { const Bytes f = FString(s); PutBytes(out, f.data(), f.size()); }
    return out;
}

// The .utoc and .ucas of a container (uncompressed, indexed, one partition), as the game's mods have them.
inline void Write(const std::string& name, const std::vector<Chunk>& chunks, Bytes& utoc, Bytes& ucas, const std::string& mount = "../../../End/Content/")
{
    const uint64_t cid = ContainerId(name);
    ucas.clear();
    struct BlockEntry { uint64_t Pos; uint32_t Size; };
    std::vector<BlockEntry> blocks;
    std::vector<std::pair<uint64_t, uint64_t>> offlen;
    uint64_t upos = 0;
    for (const Chunk& c : chunks)
    {
        const Bytes& d = *c.Data;
        offlen.emplace_back(upos, d.size());
        for (size_t i = 0; i < d.size(); i += Block)
        {
            const size_t piece = std::min<size_t>(Block, d.size() - i);
            blocks.push_back({ucas.size(), static_cast<uint32_t>(piece)});
            ucas.insert(ucas.end(), d.begin() + static_cast<long>(i), d.begin() + static_cast<long>(i + piece));
            PadTo(ucas, 16);
        }
        upos += ((d.size() + Block - 1) / Block) * Block;
    }
    std::vector<std::pair<std::string, uint32_t>> files;
    for (size_t i = 0; i < chunks.size(); ++i) { if (!chunks[i].File.empty()) { files.emplace_back(chunks[i].File, static_cast<uint32_t>(i)); } }
    const Bytes dindex = DirectoryIndex(mount, files);
    Bytes& t = utoc;
    t.clear();
    PutText(t, "-==--==--==--==-");
    PutU8(t, 2); PutU8(t, 0); PutU16(t, 0);
    for (uint32_t v : {144u, static_cast<uint32_t>(chunks.size()), static_cast<uint32_t>(blocks.size()), 12u, 0u, 32u, Block, static_cast<uint32_t>(dindex.size()), 1u}) { PutU32(t, v); }
    PutU64(t, cid);
    for (int i = 0; i < 16; ++i) { t.push_back(0); }   // encryption key guid
    PutU8(t, 8);                                        // indexed
    for (int i = 0; i < 7; ++i) { t.push_back(0); }
    PutU64(t, 0xFFFFFFFFFFFFFFFFULL);                   // partition size
    while (t.size() < 144) { t.push_back(0); }
    for (const Chunk& c : chunks) { PutU64(t, c.Id); PutU16(t, 0); PutU8(t, 0); PutU8(t, c.Type); }
    for (const auto& [off, len] : offlen)
    {
        for (int i = 4; i >= 0; --i) { t.push_back(static_cast<uint8_t>(off >> (8 * i))); }
        for (int i = 4; i >= 0; --i) { t.push_back(static_cast<uint8_t>(len >> (8 * i))); }
    }
    for (const BlockEntry& b : blocks)
    {
        for (int i = 0; i < 5; ++i) { t.push_back(static_cast<uint8_t>(b.Pos >> (8 * i))); }
        for (int i = 0; i < 3; ++i) { t.push_back(static_cast<uint8_t>(b.Size >> (8 * i))); }
        for (int i = 0; i < 3; ++i) { t.push_back(static_cast<uint8_t>(b.Size >> (8 * i))); }
        t.push_back(0);
    }
    PutBytes(t, dindex.data(), dindex.size());
    for (const Chunk& c : chunks)
    {
        const auto h = Hash::Sha1(c.Data->data(), c.Data->size());
        PutBytes(t, h.data(), h.size());
        for (int i = 0; i < 12; ++i) { t.push_back(0); }
        t.push_back(0);
    }
}

// The .pak that goes with a container (an empty pak, version 11, mount point "/"): the same for every container.
inline Bytes Pak()
{
    static const uint8_t stub[339] = {
        0x02, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa1, 0xf6, 0x1c, 0x87, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xfe, 0x40, 0x57, 0x53, 0x16, 0x6f, 0x12, 0x55, 0x59,
        0xe7, 0xc9, 0xac, 0x55, 0x86, 0x54, 0xf1, 0x07, 0xc7, 0xe9, 0x01, 0x00, 0x00, 0x00, 0x72, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x69,
        0xca, 0x78, 0xe7, 0x45, 0x0a, 0x28, 0x51, 0x73, 0x43, 0x1b, 0x3e, 0x52, 0xc5, 0xc2, 0x52, 0x99,
        0xe4, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0x12, 0x6f, 0x5a, 0x0b, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
        0xc5, 0xd2, 0x4e, 0x72, 0xab, 0x4f, 0x6d, 0x0d, 0xa5, 0xc3, 0xbb, 0xbf, 0x66, 0x97, 0xba, 0xff,
        0xaf, 0x2c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,
    };
    return Bytes(stub, stub + sizeof(stub));
}
} // namespace Container

// ---------------------------------------------------------------------------------------
// New sound banks, all the way: lines (PCM per voice language) -> HCA -> the bank -> its packages -> a container
// ---------------------------------------------------------------------------------------
namespace Build
{
// Voice languages the game has (its voice packages: JP is the source, DE, FR and US are its variants).
constexpr const char* SourceLanguage = "JP";
constexpr const char* VariantLanguages[3] = {"DE", "FR", "US"};

struct Line
{
    std::string Cue;                                   // the sound's name in the bank (what notifies and aliases play)
    std::vector<std::pair<std::string, Pcm>> Audio;    // (language, PCM); one entry with language "" for a bank of one language
    float Volume = 0.4467f;
    uint8_t Category = 0x11, Bus = 0x13;
    int Id = -1;
    float Length = -1.0f;                              // (below 0: the HCA's own)
};

struct Request
{
    std::string Container;          // the mod's name: <Container>.utoc/.ucas/.pak (end it in _P like the game's mods)
    std::string Bank;               // the bank's name (and its asset's), at most 31 characters
    uint16_t BankId = 0;            // 0: from the name
    std::string Folder;             // where it goes: /Game/Sound/Voice/{language}/Character/Player (a voice bank, one per
                                    // voice language) or any /Game/... folder (one bank)
    std::string AliasSetting;       // its alias setting (an asset path), e.g. the original character's
    std::string Attenuation = "/Game/Sound/Config/Attenuation/player";
    double Kbps = 85.25;            // per channel (the game's voice banks: 85.25)
    int Rate = 0;                   // resample to this rate first (0: keep each WAV's)
    int Channels = 0;               // mix down to this many channels first (0: keep)
    std::vector<Line> Lines;
};

struct Result
{
    bool Ok = false;
    std::string Error;
    std::vector<std::string> Report;
    std::vector<std::string> Packages;   // the package paths it made
    Bytes Utoc, Ucas, Pak;
};

inline std::string Replace(std::string s, const std::string& what, const std::string& with)
{
    const size_t at = s.find(what);
    if (at != std::string::npos) { s.replace(at, what.size(), with); }
    return s;
}

inline const Pcm* AudioFor(const Line& line, const std::string& language)
{
    for (const auto& [lang, pcm] : line.Audio) { if (lang == language) { return &pcm; } }
    return nullptr;
}

inline Result Make(const Request& request)
{
    Result r;
    auto fail = [&](const std::string& e) { r.Error = e; r.Ok = false; return r; };
    if (!Sead::ValidName(request.Bank)) { return fail("a bank name is 1-31 letters, digits, '_' or '-': " + request.Bank); }
    if (request.Container.empty() || request.Container.size() > 120 ||
        !std::all_of(request.Container.begin(), request.Container.end(), [](char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-'; }))
    {
        return fail("a container name is letters, digits, '_' or '-': " + request.Container);
    }
    if (request.Folder.rfind("/Game/", 0) != 0) { return fail("the folder must be under /Game/: " + request.Folder); }
    if (request.Lines.empty()) { return fail("a bank needs at least one line"); }
    const bool voice = request.Folder.find("{language}") != std::string::npos;
    // the languages the lines have
    std::vector<std::string> languages;
    for (const Line& l : request.Lines)
    {
        for (const auto& [lang, pcm] : l.Audio) { if (std::find(languages.begin(), languages.end(), lang) == languages.end()) { languages.push_back(lang); } }
    }
    // the packages: one bank without {language}; with it, the JP package alone for lines of one language (every
    // voice language plays them), else JP (the source) and DE, FR, US (each language's lines, else the first language's)
    std::vector<std::pair<std::string, std::string>> packages;   // (language of the lines, package path)
    const std::string first = languages.empty() ? std::string() : languages.front();
    if (!voice) { packages.emplace_back(first, request.Folder + "/" + request.Bank); }
    else if (languages.size() <= 1) { packages.emplace_back(first, Replace(request.Folder, "{language}", SourceLanguage) + "/" + request.Bank); }
    else
    {
        auto has = [&](const std::string& l) { return std::find(languages.begin(), languages.end(), l) != languages.end(); };
        const std::string fallback = has("US") ? "US" : first;
        packages.emplace_back(has(SourceLanguage) ? SourceLanguage : fallback, Replace(request.Folder, "{language}", SourceLanguage) + "/" + request.Bank);
        for (const char* v : VariantLanguages) { packages.emplace_back(has(v) ? v : fallback, Replace(request.Folder, "{language}", v) + "/" + request.Bank); }
    }
    const std::string source = packages.front().second;
    const uint16_t bankId = request.BankId ? request.BankId : Sead::IdFor(request.Bank);
    Hca::Encoder encoder;
    std::vector<Container::Package> built;
    std::vector<Bytes> datas;
    for (const auto& [language, path] : packages)
    {
        Sead::Bank bank;
        bank.Name = request.Bank;
        bank.Id = bankId;
        double seconds = 0.0;
        size_t bytes = 0;
        for (const Line& line : request.Lines)
        {
            const Pcm* found = AudioFor(line, language);
            if (!found && !line.Audio.empty()) { found = &line.Audio.front().second; }
            if (!found) { return fail("line " + line.Cue + " has no audio"); }
            Pcm pcm = *found;
            if (request.Channels > 0) { pcm = Mixdown(pcm, request.Channels); }
            if (request.Rate > 0) { pcm = Resample(pcm, request.Rate); }
            if (pcm.Frames() == 0) { pcm.Samples.assign(static_cast<size_t>(std::max(1, pcm.Channels)), 0.0f); }
            Sead::Sound s;
            s.Name = line.Cue;
            s.Volume = line.Volume;
            s.Category = line.Category;
            s.Bus = line.Bus;
            s.Id = line.Id;
            s.Length = line.Length;
            std::string error;
            s.Hca = encoder.Encode(pcm, Hca::FrameBytesFor(pcm.Rate, pcm.Channels, request.Kbps), &s.Info, &error);
            if (s.Hca.empty()) { return fail("line " + line.Cue + ": " + error); }
            seconds += s.Seconds();
            bytes += s.Hca.size();
            bank.Sounds.push_back(std::move(s));
        }
        std::string error;
        const Bytes sab = Sead::Write(bank, &error);
        if (sab.empty()) { return fail(error); }
        BankPackage::Spec spec;
        spec.Package = path;
        spec.Source = path == source ? std::string() : source;
        spec.AliasSetting = request.AliasSetting;
        spec.Attenuation = request.Attenuation;
        Bytes pkg = BankPackage::Write(spec, bank, sab, &error);
        if (pkg.empty()) { return fail(error); }
        Container::Package p;
        p.Path = path;
        p.SizeFlags = 4ULL << 60;   // its export aligned to 16 bytes (the SEAD data), as the game's banks
        if (!request.Attenuation.empty()) { p.ImportedPackages.push_back(Ids::PackageId(request.Attenuation)); }
        if (!request.AliasSetting.empty()) { p.ImportedPackages.push_back(Ids::PackageId(request.AliasSetting)); }
        std::sort(p.ImportedPackages.begin(), p.ImportedPackages.end());
        p.Data = std::move(pkg);
        r.Report.push_back(path + (language.empty() ? std::string() : " (" + language + " lines)") + ": " + std::to_string(bank.Sounds.size()) + " sounds, " +
                           std::to_string(static_cast<int>(seconds + 0.5)) + " s of audio, HCA " + std::to_string(bytes / 1024) + " KB, package " +
                           std::to_string(p.Data.size() / 1024) + " KB, bank id " + std::to_string(bankId));
        r.Packages.push_back(path);
        built.push_back(std::move(p));
    }
    std::vector<Container::Localized> localized;
    if (built.size() == 4)
    {
        Container::Localized l;
        l.Source = Ids::PackageId(built[0].Path);
        for (size_t i = 1; i < 4; ++i) { l.Variants.push_back(Ids::PackageId(built[i].Path)); }
        localized.push_back(l);
    }
    const uint64_t cid = Container::ContainerId(request.Container);
    const Bytes header = Container::Header(cid, built, localized);
    std::vector<Container::Chunk> chunks;
    chunks.push_back(Container::Chunk{cid, 10, &header, ""});
    for (const Container::Package& p : built)
    {
        chunks.push_back(Container::Chunk{Ids::PackageId(p.Path), 2, &p.Data, p.Path.substr(6) + ".uasset"});
    }
    Container::Write(request.Container, chunks, r.Utoc, r.Ucas);
    r.Pak = Container::Pak();
    r.Ok = true;
    return r;
}
} // namespace Build
} // namespace CacsSound
