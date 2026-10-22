// SkinCore.hpp
// Create a Character System skins (editor 1.15, game mod 3.10). A skin is a folder of the game's own (zen) packages
// with a skin.json:
//
//   skins/<Folder>/skin.json
//   skins/<Folder>/Content/<path under /Game>.uasset   (+ .ubulk / .uptnl / .m.ubulk: the package's bulk data)
//   skins/<Folder>/preview.png                         (optional)
//
// This header is what the editor's Build Skins and the game mod share:
//   - reading an uncompressed IoStore container (.utoc + .ucas), such as the engine's IoStore commandlet writes;
//   - the packages of such a container with the store entries its container header gives them (ExtractPackages);
//   - skin.json, written and read (64-bit numbers kept exact);
//   - the skins container, CreateACharacterSkins_P (.utoc/.ucas/.pak in ~mods), made from every skin folder
//     (BuildCache): the game only loads zen packages from a mounted container.
//
// Portable C++17 without engine or OS types, without exceptions and without file access (the callers read and write
// the files), like SoundBankCore.hpp, whose ids and container writer it uses.
#pragma once

#include "SoundBankCore.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace CacsSkin
{
using CacsSound::Bytes;

constexpr const char* Schema = "CreateACharacterSkin/1";
constexpr const char* CacheName = "CreateACharacterSkins_P";
constexpr const char* ContentMount = "../../../End/Content/";   // where the game's /Game packages are in a container
constexpr uint64_t SizeMask = (1ULL << 60) - 1;                  // a store entry's size; the bits above are flags

// EIoChunkType (UE 4.26)
constexpr uint8_t ExportBundleData = 2;
constexpr uint8_t BulkData = 3;
constexpr uint8_t OptionalBulkData = 4;
constexpr uint8_t MemoryMappedBulkData = 5;
constexpr uint8_t ContainerHeaderChunk = 10;

inline bool EndsWith(const std::string& s, const char* tail)
{
    const size_t n = std::strlen(tail);
    return s.size() >= n && s.compare(s.size() - n, n, tail) == 0;
}

inline bool StartsWith(const std::string& s, const char* head)
{
    const size_t n = std::strlen(head);
    return s.size() >= n && s.compare(0, n, head) == 0;
}

// The file extension of a package's chunk (nullptr: not one of a package's).
inline const char* ExtensionOf(uint8_t type)
{
    switch (type)
    {
    case ExportBundleData: return ".uasset";
    case BulkData: return ".ubulk";
    case OptionalBulkData: return ".uptnl";
    case MemoryMappedBulkData: return ".m.ubulk";
    default: return nullptr;
    }
}

// The chunk type of a package file by its extension (0: none).
inline uint8_t TypeOfFile(const std::string& file)
{
    if (EndsWith(file, ".m.ubulk")) { return MemoryMappedBulkData; }
    if (EndsWith(file, ".ubulk")) { return BulkData; }
    if (EndsWith(file, ".uptnl")) { return OptionalBulkData; }
    if (EndsWith(file, ".uasset")) { return ExportBundleData; }
    return 0;
}

inline std::string Hex16(uint64_t v)
{
    char text[17];
    std::snprintf(text, sizeof(text), "%016llx", static_cast<unsigned long long>(v));
    return text;
}

// "4c3231f50d86c3a2" or "0x4C32..." -> the number; false when it is not 1-16 hex digits.
inline bool ParseHex64(const std::string& text, uint64_t& out)
{
    size_t i = StartsWith(text, "0x") || StartsWith(text, "0X") ? 2 : 0;
    if (i >= text.size() || text.size() - i > 16) { return false; }
    uint64_t v = 0;
    for (; i < text.size(); ++i)
    {
        const char c = text[i];
        int d = -1;
        if (c >= '0' && c <= '9') { d = c - '0'; }
        else if (c >= 'a' && c <= 'f') { d = c - 'a' + 10; }
        else if (c >= 'A' && c <= 'F') { d = c - 'A' + 10; }
        if (d < 0) { return false; }
        v = (v << 4) | static_cast<uint64_t>(d);
    }
    out = v;
    return true;
}

inline void AppendUtf8(std::string& out, uint32_t cp)
{
    if (cp < 0x80) { out += static_cast<char>(cp); }
    else if (cp < 0x800) { out += static_cast<char>(0xC0 | (cp >> 6)); out += static_cast<char>(0x80 | (cp & 0x3F)); }
    else if (cp < 0x10000)
    {
        out += static_cast<char>(0xE0 | (cp >> 12)); out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (cp & 0x3F));
    }
    else
    {
        out += static_cast<char>(0xF0 | (cp >> 18)); out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
        out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F)); out += static_cast<char>(0x80 | (cp & 0x3F));
    }
}

// ---------------------------------------------------------------------------------------
// Reading an IoStore container (.utoc + .ucas), uncompressed
// ---------------------------------------------------------------------------------------
struct TocBlock
{
    uint64_t Offset = 0;                 // in the .ucas
    uint32_t CompressedSize = 0;
    uint32_t UncompressedSize = 0;
    uint8_t Method = 0;                  // 0: none, else 1 + the index of a compression method name
};

struct TocChunk
{
    uint64_t Id = 0;                     // a package's FPackageId for a package's chunks
    uint16_t Index = 0;
    uint8_t Type = 0;                    // EIoChunkType
    uint64_t Offset = 0;                 // in the container's uncompressed data
    uint64_t Length = 0;
    std::string Path;                    // from the directory index, relative to Toc::Mount ("": none)
};

struct Toc
{
    uint8_t Version = 0;
    uint32_t BlockSize = 0;
    uint8_t Flags = 0;                   // EIoContainerFlags: 1 compressed, 2 encrypted, 4 signed, 8 indexed
    uint64_t ContainerId = 0;
    std::string Mount;                   // the directory index's mount point, e.g. ../../../End/Content/GameContents/
    std::vector<TocChunk> Chunks;
    std::vector<TocBlock> Blocks;
    std::vector<std::string> Methods;
};

namespace Detail
{
struct Reader
{
    const uint8_t* Data = nullptr;
    size_t Size = 0;
    size_t At = 0;
    bool Ok = true;

    Reader(const uint8_t* data, size_t size) : Data(data), Size(size) {}

    bool Need(size_t n)
    {
        if (Ok && (n > Size || At > Size - n)) { Ok = false; }
        return Ok;
    }
    uint8_t U8() { if (!Need(1)) { return 0; } return Data[At++]; }
    uint16_t U16() { if (!Need(2)) { return 0; } const uint16_t v = CacsSound::GetU16(Data + At); At += 2; return v; }
    uint32_t U32() { if (!Need(4)) { return 0; } const uint32_t v = CacsSound::GetU32(Data + At); At += 4; return v; }
    int32_t I32() { return static_cast<int32_t>(U32()); }
    uint64_t U64() { if (!Need(8)) { return 0; } const uint64_t v = CacsSound::GetU64(Data + At); At += 8; return v; }
    uint64_t BigEndian(size_t n)
    {
        if (!Need(n)) { return 0; }
        uint64_t v = 0;
        for (size_t i = 0; i < n; ++i) { v = (v << 8) | Data[At + i]; }
        At += n;
        return v;
    }
    uint64_t LittleEndian(size_t n)
    {
        if (!Need(n)) { return 0; }
        uint64_t v = 0;
        for (size_t i = 0; i < n; ++i) { v |= static_cast<uint64_t>(Data[At + i]) << (8 * i); }
        At += n;
        return v;
    }
    void Skip(size_t n) { if (Need(n)) { At += n; } }
    // An FString: a positive length is ANSI bytes, a negative one UTF-16 code units (both with the closing NUL).
    std::string FString()
    {
        const int32_t len = I32();
        std::string out;
        if (!Ok || len == 0) { return out; }
        if (len > 0)
        {
            if (!Need(static_cast<size_t>(len))) { return out; }
            for (int32_t i = 0; i < len; ++i)
            {
                const uint8_t c = Data[At + static_cast<size_t>(i)];
                if (c == 0) { break; }
                AppendUtf8(out, c);
            }
            At += static_cast<size_t>(len);
            return out;
        }
        if (len == INT32_MIN) { Ok = false; return out; }
        const size_t units = static_cast<size_t>(-static_cast<int64_t>(len));
        if (units > Size || !Need(units * 2)) { Ok = false; return out; }
        for (size_t i = 0; i < units; ++i)
        {
            uint32_t u = CacsSound::GetU16(Data + At + 2 * i);
            if (u == 0) { break; }
            if (u >= 0xD800 && u < 0xDC00 && i + 1 < units)
            {
                const uint32_t lo = CacsSound::GetU16(Data + At + 2 * (i + 1));
                if (lo >= 0xDC00 && lo < 0xE000) { u = 0x10000 + ((u - 0xD800) << 10) + (lo - 0xDC00); ++i; }
            }
            AppendUtf8(out, u);
        }
        At += units * 2;
        return out;
    }
};
} // namespace Detail

inline bool ReadToc(const uint8_t* data, size_t size, Toc& toc, std::string& error)
{
    toc = Toc{};
    Detail::Reader r(data, size);
    static const char Magic[] = "-==--==--==--==-";
    if (size < 144 || std::memcmp(data, Magic, 16) != 0) { error = "not a .utoc (no TOC magic)"; return false; }
    r.Skip(16);
    toc.Version = r.U8();
    r.Skip(3);
    const uint32_t headerSize = r.U32();
    const uint32_t entryCount = r.U32();
    const uint32_t blockCount = r.U32();
    const uint32_t blockEntrySize = r.U32();
    const uint32_t methodCount = r.U32();
    const uint32_t methodLength = r.U32();
    toc.BlockSize = r.U32();
    const uint32_t directorySize = r.U32();
    r.U32();                                         // partition count
    toc.ContainerId = r.U64();
    r.Skip(16);                                      // encryption key guid
    toc.Flags = r.U8();
    if (toc.Version < 1 || toc.Version > 3) { error = "TOC version " + std::to_string(toc.Version) + " is not one of UE 4.26's (1-3)"; return false; }
    if (headerSize < 144 || headerSize > size || blockEntrySize != 12 || toc.BlockSize == 0)
    {
        error = "TOC header does not read (header size " + std::to_string(headerSize) + ", block entry size " + std::to_string(blockEntrySize) + ")";
        return false;
    }
    if (toc.Flags & 2) { error = "the container is encrypted"; return false; }
    r.At = headerSize;
    if (static_cast<uint64_t>(entryCount) * 22 + static_cast<uint64_t>(blockCount) * 12 > size) { error = "TOC counts are larger than the file"; return false; }
    toc.Chunks.resize(entryCount);
    for (TocChunk& c : toc.Chunks)
    {
        c.Id = r.U64();
        c.Index = static_cast<uint16_t>(r.BigEndian(2));
        r.U8();
        c.Type = r.U8();
    }
    for (TocChunk& c : toc.Chunks)
    {
        c.Offset = r.BigEndian(5);
        c.Length = r.BigEndian(5);
    }
    toc.Blocks.resize(blockCount);
    for (TocBlock& b : toc.Blocks)
    {
        b.Offset = r.LittleEndian(5);
        b.CompressedSize = static_cast<uint32_t>(r.LittleEndian(3));
        b.UncompressedSize = static_cast<uint32_t>(r.LittleEndian(3));
        b.Method = r.U8();
    }
    for (uint32_t i = 0; i < methodCount && r.Ok; ++i)
    {
        if (!r.Need(methodLength)) { break; }
        std::string name;
        for (uint32_t k = 0; k < methodLength && data[r.At + k] != 0; ++k) { name += static_cast<char>(data[r.At + k]); }
        toc.Methods.push_back(name);
        r.At += methodLength;
    }
    if (toc.Flags & 4)
    {
        const int32_t hashSize = r.I32();
        if (hashSize < 0) { error = "the TOC signature does not read"; return false; }
        r.Skip(2 * static_cast<size_t>(hashSize) + 20 * static_cast<size_t>(blockCount));
    }
    if (!r.Ok) { error = "the TOC is cut short"; return false; }
    if (directorySize > 0)
    {
        if (!r.Need(directorySize)) { error = "the TOC's directory index is cut short"; return false; }
        Detail::Reader d(data + r.At, directorySize);
        toc.Mount = d.FString();
        const int32_t dirCount = d.I32();
        if (!d.Ok || dirCount < 0 || static_cast<uint64_t>(dirCount) * 16 > directorySize) { error = "the directory index does not read"; return false; }
        struct Dir { uint32_t Name, FirstChild, NextSibling, FirstFile; };
        std::vector<Dir> dirs(static_cast<size_t>(dirCount));
        for (Dir& x : dirs) { x.Name = d.U32(); x.FirstChild = d.U32(); x.NextSibling = d.U32(); x.FirstFile = d.U32(); }
        const int32_t fileCount = d.I32();
        if (!d.Ok || fileCount < 0 || static_cast<uint64_t>(fileCount) * 12 > directorySize) { error = "the directory index does not read"; return false; }
        struct File { uint32_t Name, Next, Chunk; };
        std::vector<File> files(static_cast<size_t>(fileCount));
        for (File& f : files) { f.Name = d.U32(); f.Next = d.U32(); f.Chunk = d.U32(); }
        const int32_t stringCount = d.I32();
        if (!d.Ok || stringCount < 0 || static_cast<uint64_t>(stringCount) * 4 > directorySize) { error = "the directory index does not read"; return false; }
        std::vector<std::string> strings(static_cast<size_t>(stringCount));
        for (std::string& s : strings) { s = d.FString(); }
        if (!d.Ok) { error = "the directory index's names do not read"; return false; }
        const uint32_t none = 0xFFFFFFFFu;
        // the tree, from the root (directory 0, no name), with a visit budget against a damaged index
        std::vector<std::pair<uint32_t, std::string>> stack;
        if (!dirs.empty()) { stack.emplace_back(0u, std::string()); }
        size_t visits = 0;
        while (!stack.empty())
        {
            const auto [index, prefix] = stack.back();
            stack.pop_back();
            if (index >= dirs.size() || ++visits > dirs.size() + files.size() + 1) { error = "the directory index is damaged"; return false; }
            const Dir& x = dirs[index];
            std::string here = prefix;
            if (x.Name != none)
            {
                if (x.Name >= strings.size()) { error = "the directory index is damaged"; return false; }
                here += strings[x.Name] + "/";
            }
            size_t guard = 0;
            for (uint32_t f = x.FirstFile; f != none; f = files[f].Next)
            {
                if (f >= files.size() || files[f].Name >= strings.size() || files[f].Chunk >= toc.Chunks.size() || ++guard > files.size())
                {
                    error = "the directory index is damaged";
                    return false;
                }
                toc.Chunks[files[f].Chunk].Path = here + strings[files[f].Name];
            }
            // children pushed last to first, so the first child is walked first (as a recursive walk would)
            std::vector<uint32_t> children;
            guard = 0;
            for (uint32_t c = x.FirstChild; c != none; c = dirs[c].NextSibling)
            {
                if (c >= dirs.size() || ++guard > dirs.size()) { error = "the directory index is damaged"; return false; }
                children.push_back(c);
            }
            for (auto it = children.rbegin(); it != children.rend(); ++it) { stack.emplace_back(*it, here); }
        }
    }
    return true;
}

// The bytes of one chunk (Toc::Chunks[index]) from the .ucas. Compressed blocks are refused.
inline bool ReadChunk(const Toc& toc, const uint8_t* ucas, size_t ucasSize, size_t index, Bytes& out, std::string& error)
{
    out.clear();
    if (index >= toc.Chunks.size()) { error = "no chunk " + std::to_string(index); return false; }
    const TocChunk& c = toc.Chunks[index];
    if (c.Length == 0) { return true; }
    uint64_t block = c.Offset / toc.BlockSize;
    const uint64_t skip = c.Offset % toc.BlockSize;
    const uint64_t want = c.Length + skip;
    out.reserve(static_cast<size_t>(want));
    while (out.size() < want)
    {
        if (block >= toc.Blocks.size()) { error = "chunk " + std::to_string(index) + " runs past the TOC's blocks"; return false; }
        const TocBlock& b = toc.Blocks[static_cast<size_t>(block)];
        if (b.Method != 0)
        {
            const std::string method = b.Method <= toc.Methods.size() ? toc.Methods[b.Method - 1] : std::string("method ") + std::to_string(b.Method);
            error = "the container is compressed (" + method + "): build it without compression";
            return false;
        }
        if (b.UncompressedSize > b.CompressedSize || b.Offset > ucasSize || b.UncompressedSize > ucasSize - b.Offset)
        {
            error = "block " + std::to_string(block) + " lies outside the .ucas";
            return false;
        }
        out.insert(out.end(), ucas + b.Offset, ucas + b.Offset + b.UncompressedSize);
        ++block;
    }
    out.erase(out.begin(), out.begin() + static_cast<long>(skip));
    out.resize(static_cast<size_t>(c.Length));
    return true;
}

// ---------------------------------------------------------------------------------------
// A container header (the game's layout: UE 4.26's with a count of localization records after the package count)
// ---------------------------------------------------------------------------------------
struct StoreEntry
{
    uint64_t Id = 0;                     // FPackageId
    uint64_t Size = 0;                   // the zen package's size (bits 60+: flags)
    int32_t ExportCount = 0;
    int32_t BundleCount = 0;
    uint32_t LoadOrder = 0;
    uint32_t Record = 0xFFFFFFFFu;       // a localization record's offset, or none
    std::vector<uint64_t> Imports;       // the package ids it imports
};

struct ContainerHeaderInfo
{
    uint64_t ContainerId = 0;
    uint32_t Records = 0;
    std::vector<StoreEntry> Entries;
};

inline bool ReadContainerHeader(const uint8_t* data, size_t size, ContainerHeaderInfo& out, std::string& error)
{
    out = ContainerHeaderInfo{};
    Detail::Reader r(data, size);
    out.ContainerId = r.U64();
    const uint32_t count = r.U32();
    out.Records = r.U32();
    for (int i = 0; i < 2; ++i)                      // names, name hashes
    {
        const int32_t n = r.I32();
        if (n < 0) { r.Ok = false; }
        r.Skip(static_cast<size_t>(n));
    }
    const int32_t idCount = r.I32();
    if (!r.Ok || idCount < 0 || static_cast<uint32_t>(idCount) != count || !r.Need(static_cast<size_t>(idCount) * 8))
    {
        error = "the container header's package ids do not read";
        return false;
    }
    std::vector<uint64_t> ids(static_cast<size_t>(idCount));
    for (uint64_t& id : ids) { id = r.U64(); }
    const int32_t storeSize = r.I32();
    if (!r.Ok || storeSize < 0 || !r.Need(static_cast<size_t>(storeSize)) || static_cast<uint64_t>(storeSize) < static_cast<uint64_t>(count) * 32)
    {
        error = "the container header's store entries do not read";
        return false;
    }
    const uint8_t* store = data + r.At;
    for (uint32_t i = 0; i < count; ++i)
    {
        const uint8_t* e = store + static_cast<size_t>(i) * 32;
        StoreEntry entry;
        entry.Id = ids[i];
        entry.Size = CacsSound::GetU64(e);
        entry.ExportCount = static_cast<int32_t>(CacsSound::GetU32(e + 8));
        entry.BundleCount = static_cast<int32_t>(CacsSound::GetU32(e + 12));
        entry.LoadOrder = CacsSound::GetU32(e + 16);
        entry.Record = CacsSound::GetU32(e + 20);
        const uint32_t importCount = CacsSound::GetU32(e + 24);
        const uint32_t offset = CacsSound::GetU32(e + 28);
        if (importCount > 0)
        {
            const uint64_t at = static_cast<uint64_t>(i) * 32 + 24 + offset;
            if (at + static_cast<uint64_t>(importCount) * 8 > static_cast<uint64_t>(storeSize))
            {
                error = "store entry " + std::to_string(i) + "'s imports lie outside the store entries";
                return false;
            }
            for (uint32_t k = 0; k < importCount; ++k) { entry.Imports.push_back(CacsSound::GetU64(store + at + 8ULL * k)); }
        }
        out.Entries.push_back(std::move(entry));
    }
    return true;
}

// ---------------------------------------------------------------------------------------
// Skins
// ---------------------------------------------------------------------------------------
struct SkinBulk
{
    std::string File;                    // in the skin folder: Content/<path>.ubulk
    uint8_t Type = BulkData;
    Bytes Data;
};

struct SkinPackage
{
    std::string Package;                 // /Game/...
    std::string File;                    // in the skin folder: Content/<path>.uasset
    uint64_t Size = 0;                   // its store entry's
    int32_t ExportCount = 0;
    int32_t BundleCount = 0;
    uint32_t LoadOrder = 0;
    std::vector<uint64_t> Imports;
    Bytes Data;                          // the zen package (not in skin.json)
    std::vector<SkinBulk> Bulk;
};

// What skin.json holds.
struct SkinInfo
{
    std::string Name;
    std::string Author;
    std::string Description;
    std::vector<std::string> Characters; // CharaSpec rows that wear it, e.g. PC0000_00_Cloud_Standard
    std::string Model;                   // object paths: /Game/.../EB0021_00.EB0021_00
    std::string Skeleton;
    std::string Family;                  // the hub skeleton the model's skeleton joins ("": none)
    bool Proportions = false;
    std::vector<std::string> ProportionBones;
    std::string Voice;                   // "own", "" (the row's), or a voice bank path with {language}
    std::string Weapon;                  // a weapon blueprint class, "" (its own)
    std::string AnimBlueprint;           // "" (the character's own)
    bool Enabled = true;
    std::string Preview;                 // "preview.png" or ""
    std::vector<SkinPackage> Packages;
    std::string Built;                   // UTC, 2026-10-21T23:12:19Z
    std::string BuiltWith;
};

// The packages of an engine-made container (the IoStore commandlet's), in its container header's order: each one's
// zen package and bulk data with the file names they have in a skin folder, and its store entry.
inline bool ExtractPackages(const Toc& toc, const uint8_t* ucas, size_t ucasSize, std::vector<SkinPackage>& out, std::string& error)
{
    out.clear();
    ContainerHeaderInfo header;
    bool haveHeader = false;
    struct Part { uint8_t Type; std::string File; size_t Chunk; };
    std::map<uint64_t, std::vector<Part>> parts;
    const size_t mountLength = std::strlen(ContentMount);
    for (size_t i = 0; i < toc.Chunks.size(); ++i)
    {
        const TocChunk& c = toc.Chunks[i];
        if (c.Type == ContainerHeaderChunk)
        {
            Bytes data;
            if (!ReadChunk(toc, ucas, ucasSize, i, data, error) || !ReadContainerHeader(data.data(), data.size(), header, error)) { return false; }
            haveHeader = true;
            continue;
        }
        const char* extension = ExtensionOf(c.Type);
        if (!extension) { error = "chunk " + std::to_string(i) + " is of type " + std::to_string(c.Type) + ", not one of a package's"; return false; }
        if (c.Path.empty()) { error = "chunk " + std::to_string(i) + " has no file name (the container has no directory index)"; return false; }
        const std::string full = toc.Mount + c.Path;
        if (!StartsWith(full, ContentMount)) { error = full + " is not under " + ContentMount + " (/Game)"; return false; }
        const std::string file = "Content/" + full.substr(mountLength);
        if (!EndsWith(file, extension)) { error = file + " is not a " + extension + " file, as its chunk type says"; return false; }
        parts[c.Id].push_back(Part{c.Type, file, i});
    }
    if (!haveHeader) { error = "the container has no container header"; return false; }
    std::set<uint64_t> used;
    for (const StoreEntry& e : header.Entries)
    {
        auto it = parts.find(e.Id);
        const Part* main = nullptr;
        if (it != parts.end())
        {
            for (const Part& p : it->second) { if (p.Type == ExportBundleData && !main) { main = &p; } }
        }
        if (!main) { error = "package " + Hex16(e.Id) + " of the container header has no package chunk"; return false; }
        SkinPackage pkg;
        pkg.File = main->File;
        pkg.Package = "/Game/" + main->File.substr(8, main->File.size() - 8 - 7);   // Content/<path>.uasset -> /Game/<path>
        if (CacsSound::Ids::PackageId(pkg.Package) != e.Id) { error = pkg.Package + "'s package id is not " + Hex16(e.Id); return false; }
        pkg.Size = e.Size;
        pkg.ExportCount = e.ExportCount;
        pkg.BundleCount = e.BundleCount;
        pkg.LoadOrder = e.LoadOrder;
        pkg.Imports = e.Imports;
        if (!ReadChunk(toc, ucas, ucasSize, main->Chunk, pkg.Data, error)) { return false; }
        if (pkg.Data.size() != (e.Size & SizeMask))
        {
            error = pkg.Package + " is " + std::to_string(pkg.Data.size()) + " bytes, its store entry says " + std::to_string(e.Size & SizeMask);
            return false;
        }
        for (const Part& p : it->second)
        {
            if (&p == main) { continue; }
            if (p.Type == ExportBundleData) { error = pkg.Package + " has two package chunks"; return false; }
            SkinBulk bulk;
            bulk.File = p.File;
            bulk.Type = p.Type;
            if (!ReadChunk(toc, ucas, ucasSize, p.Chunk, bulk.Data, error)) { return false; }
            pkg.Bulk.push_back(std::move(bulk));
        }
        used.insert(e.Id);
        out.push_back(std::move(pkg));
    }
    for (const auto& [id, list] : parts)
    {
        if (!used.count(id)) { error = list.front().File + " is not in the container header"; return false; }
    }
    return true;
}

// Every file a skin folder has by its skin.json (packages, their bulk data, the preview), as skin.json names them.
inline std::vector<std::string> FilesOf(const SkinInfo& skin)
{
    std::vector<std::string> files;
    for (const SkinPackage& p : skin.Packages)
    {
        files.push_back(p.File);
        for (const SkinBulk& b : p.Bulk) { files.push_back(b.File); }
    }
    if (!skin.Preview.empty()) { files.push_back(skin.Preview); }
    return files;
}

// A file name skin.json may give: relative, forward slashes, no "..", no drive or root.
inline bool SafeRelativePath(const std::string& path)
{
    if (path.empty() || path[0] == '/' || path[0] == '\\' || path.find(':') != std::string::npos || path.find('\\') != std::string::npos) { return false; }
    size_t start = 0;
    while (start <= path.size())
    {
        size_t slash = path.find('/', start);
        if (slash == std::string::npos) { slash = path.size(); }
        const std::string part = path.substr(start, slash - start);
        if (part.empty() || part == "." || part == "..") { return false; }
        start = slash + 1;
    }
    return true;
}

// ---------------------------------------------------------------------------------------
// JSON (skin.json): a small reader keeping numbers as text, and the writer
// ---------------------------------------------------------------------------------------
struct Json
{
    enum class Kind { Null, Bool, Number, String, Array, Object };
    Kind Type = Kind::Null;
    bool Boolean = false;
    std::string Text;                    // a string's UTF-8, or a number as written
    std::vector<Json> Items;
    std::vector<std::pair<std::string, Json>> Fields;

    const Json* Find(const char* key) const
    {
        for (const auto& [k, v] : Fields) { if (k == key) { return &v; } }
        return nullptr;
    }
};

namespace Detail
{
struct JsonParser
{
    const std::string& S;
    size_t At = 0;
    std::string Error;

    explicit JsonParser(const std::string& text) : S(text) {}

    void Space() { while (At < S.size() && (S[At] == ' ' || S[At] == '\t' || S[At] == '\r' || S[At] == '\n')) { ++At; } }
    bool Fail(const std::string& why) { if (Error.empty()) { Error = why + " at character " + std::to_string(At); } return false; }

    bool Hex4(uint32_t& out)
    {
        if (At + 4 > S.size()) { return Fail("a short \\u escape"); }
        uint32_t v = 0;
        for (size_t k = 0; k < 4; ++k)
        {
            const char c = S[At + k];
            int d = -1;
            if (c >= '0' && c <= '9') { d = c - '0'; }
            else if (c >= 'a' && c <= 'f') { d = c - 'a' + 10; }
            else if (c >= 'A' && c <= 'F') { d = c - 'A' + 10; }
            if (d < 0) { return Fail("a bad \\u escape"); }
            v = (v << 4) | static_cast<uint32_t>(d);
        }
        out = v;
        At += 4;
        return true;
    }

    bool String(std::string& out)
    {
        if (At >= S.size() || S[At] != '"') { return Fail("a string expected"); }
        ++At;
        while (At < S.size())
        {
            const char c = S[At++];
            if (c == '"') { return true; }
            if (static_cast<unsigned char>(c) < 0x20) { return Fail("a control character in a string"); }
            if (c != '\\') { out += c; continue; }
            if (At >= S.size()) { break; }
            const char e = S[At++];
            switch (e)
            {
            case '"': out += '"'; break;
            case '\\': out += '\\'; break;
            case '/': out += '/'; break;
            case 'b': out += '\b'; break;
            case 'f': out += '\f'; break;
            case 'n': out += '\n'; break;
            case 'r': out += '\r'; break;
            case 't': out += '\t'; break;
            case 'u':
            {
                uint32_t cp = 0;
                if (!Hex4(cp)) { return false; }
                if (cp >= 0xD800 && cp < 0xDC00 && At + 6 <= S.size() && S[At] == '\\' && S[At + 1] == 'u')
                {
                    At += 2;
                    uint32_t lo = 0;
                    if (!Hex4(lo)) { return false; }
                    if (lo >= 0xDC00 && lo < 0xE000) { cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00); }
                    else { AppendUtf8(out, cp); cp = lo; }
                }
                AppendUtf8(out, cp);
                break;
            }
            default: return Fail("a bad escape");
            }
        }
        return Fail("an unterminated string");
    }

    bool Value(Json& out, int depth)
    {
        if (depth > 64) { return Fail("too deep"); }
        Space();
        if (At >= S.size()) { return Fail("a value expected"); }
        const char c = S[At];
        if (c == '{')
        {
            out.Type = Json::Kind::Object;
            ++At;
            Space();
            if (At < S.size() && S[At] == '}') { ++At; return true; }
            for (;;)
            {
                Space();
                std::string key;
                if (!String(key)) { return false; }
                Space();
                if (At >= S.size() || S[At] != ':') { return Fail("':' expected"); }
                ++At;
                Json value;
                if (!Value(value, depth + 1)) { return false; }
                out.Fields.emplace_back(std::move(key), std::move(value));
                Space();
                if (At < S.size() && S[At] == ',') { ++At; continue; }
                if (At < S.size() && S[At] == '}') { ++At; return true; }
                return Fail("',' or '}' expected");
            }
        }
        if (c == '[')
        {
            out.Type = Json::Kind::Array;
            ++At;
            Space();
            if (At < S.size() && S[At] == ']') { ++At; return true; }
            for (;;)
            {
                Json value;
                if (!Value(value, depth + 1)) { return false; }
                out.Items.push_back(std::move(value));
                Space();
                if (At < S.size() && S[At] == ',') { ++At; continue; }
                if (At < S.size() && S[At] == ']') { ++At; return true; }
                return Fail("',' or ']' expected");
            }
        }
        if (c == '"') { out.Type = Json::Kind::String; return String(out.Text); }
        if (S.compare(At, 4, "true") == 0) { out.Type = Json::Kind::Bool; out.Boolean = true; At += 4; return true; }
        if (S.compare(At, 5, "false") == 0) { out.Type = Json::Kind::Bool; out.Boolean = false; At += 5; return true; }
        if (S.compare(At, 4, "null") == 0) { out.Type = Json::Kind::Null; At += 4; return true; }
        if (c == '-' || (c >= '0' && c <= '9'))
        {
            const size_t start = At;
            if (S[At] == '-') { ++At; }
            while (At < S.size() && ((S[At] >= '0' && S[At] <= '9') || S[At] == '.' || S[At] == 'e' || S[At] == 'E' || S[At] == '+' || S[At] == '-')) { ++At; }
            out.Type = Json::Kind::Number;
            out.Text = S.substr(start, At - start);
            return true;
        }
        return Fail("a value expected");
    }
};

// A JSON string of UTF-8 text, everything outside printable ASCII as \uXXXX (UTF-16), as Python's json writes it.
inline void Quote(std::string& out, const std::string& s)
{
    out += '"';
    size_t i = 0;
    while (i < s.size())
    {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        if (c == '"') { out += "\\\""; ++i; continue; }
        if (c == '\\') { out += "\\\\"; ++i; continue; }
        if (c == '\n') { out += "\\n"; ++i; continue; }
        if (c == '\r') { out += "\\r"; ++i; continue; }
        if (c == '\t') { out += "\\t"; ++i; continue; }
        if (c >= 0x20 && c < 0x80) { out += static_cast<char>(c); ++i; continue; }
        // one UTF-8 sequence (a broken one: U+FFFD for its first byte)
        uint32_t cp = 0xFFFD;
        size_t length = 1;
        if (c < 0x20) { cp = c; }
        else if ((c & 0xE0) == 0xC0) { cp = c & 0x1Fu; length = 2; }
        else if ((c & 0xF0) == 0xE0) { cp = c & 0x0Fu; length = 3; }
        else if ((c & 0xF8) == 0xF0) { cp = c & 0x07u; length = 4; }
        if (length > 1)
        {
            bool good = i + length <= s.size();
            for (size_t k = 1; good && k < length; ++k)
            {
                const unsigned char n = static_cast<unsigned char>(s[i + k]);
                if ((n & 0xC0) != 0x80) { good = false; break; }
                cp = (cp << 6) | (n & 0x3Fu);
            }
            if (!good) { cp = 0xFFFD; length = 1; }
        }
        i += length;
        char buffer[16];
        if (cp >= 0x10000 && cp <= 0x10FFFF)
        {
            const uint32_t v = cp - 0x10000;
            std::snprintf(buffer, sizeof(buffer), "\\u%04x\\u%04x", static_cast<unsigned>(0xD800 + (v >> 10)), static_cast<unsigned>(0xDC00 + (v & 0x3FF)));
        }
        else { std::snprintf(buffer, sizeof(buffer), "\\u%04x", static_cast<unsigned>(cp > 0xFFFF ? 0xFFFD : cp)); }
        out += buffer;
    }
    out += '"';
}
} // namespace Detail

inline bool ParseJson(const std::string& text, Json& out, std::string& error)
{
    out = Json{};
    Detail::JsonParser p(text);
    if (text.size() >= 3 && static_cast<unsigned char>(text[0]) == 0xEF && static_cast<unsigned char>(text[1]) == 0xBB && static_cast<unsigned char>(text[2]) == 0xBF) { p.At = 3; }
    if (!p.Value(out, 0)) { error = p.Error; return false; }
    p.Space();
    if (p.At != text.size()) { error = "text after the JSON at character " + std::to_string(p.At); return false; }
    return true;
}

// A JSON number as an unsigned 64-bit integer, exactly (false: not a whole number from 0 to 2^64-1).
inline bool JsonU64(const Json& v, uint64_t& out)
{
    if (v.Type != Json::Kind::Number || v.Text.empty()) { return false; }
    uint64_t n = 0;
    for (const char c : v.Text)
    {
        if (c < '0' || c > '9') { return false; }
        const uint64_t d = static_cast<uint64_t>(c - '0');
        if (n > (UINT64_MAX - d) / 10) { return false; }
        n = n * 10 + d;
    }
    out = n;
    return true;
}

inline bool JsonI32(const Json& v, int32_t& out)
{
    if (v.Type != Json::Kind::Number || v.Text.empty()) { return false; }
    const bool negative = v.Text[0] == '-';
    Json magnitude;
    magnitude.Type = Json::Kind::Number;
    magnitude.Text = negative ? v.Text.substr(1) : v.Text;
    uint64_t n = 0;
    if (!JsonU64(magnitude, n) || n > (negative ? 2147483648ULL : 2147483647ULL)) { return false; }
    out = negative ? static_cast<int32_t>(-static_cast<int64_t>(n)) : static_cast<int32_t>(n);
    return true;
}

// skin.json as Build Skins writes it (one-space indent, like the prototype's Python).
inline std::string WriteSkinJson(const SkinInfo& s)
{
    using Detail::Quote;
    std::string o = "{\n";
    auto key = [&](const char* k, int indent) { o.append(static_cast<size_t>(indent), ' '); Quote(o, k); o += ": "; };
    auto text = [&](const char* k, const std::string& v, bool comma = true) { key(k, 1); Quote(o, v); o += comma ? ",\n" : "\n"; };
    auto flag = [&](const char* k, bool v) { key(k, 1); o += v ? "true" : "false"; o += ",\n"; };
    auto list = [&](const char* k, const std::vector<std::string>& v, int indent) {
        key(k, indent);
        if (v.empty()) { o += "[],\n"; return; }
        o += "[\n";
        for (size_t i = 0; i < v.size(); ++i)
        {
            o.append(static_cast<size_t>(indent + 1), ' ');
            Quote(o, v[i]);
            o += i + 1 < v.size() ? ",\n" : "\n";
        }
        o.append(static_cast<size_t>(indent), ' ');
        o += "],\n";
    };
    text("schema", Schema);
    text("name", s.Name);
    text("author", s.Author);
    text("description", s.Description);
    list("characters", s.Characters, 1);
    text("model", s.Model);
    text("skeleton", s.Skeleton);
    text("family", s.Family);
    flag("proportions", s.Proportions);
    list("proportion_bones", s.ProportionBones, 1);
    text("voice", s.Voice);
    text("weapon", s.Weapon);
    text("anim_blueprint", s.AnimBlueprint);
    flag("enabled", s.Enabled);
    text("preview", s.Preview);
    key("packages", 1);
    if (s.Packages.empty()) { o += "[],\n"; }
    else
    {
        o += "[\n";
        for (size_t i = 0; i < s.Packages.size(); ++i)
        {
            const SkinPackage& p = s.Packages[i];
            o += "  {\n";
            key("package", 3); Quote(o, p.Package); o += ",\n";
            key("file", 3); Quote(o, p.File); o += ",\n";
            key("size", 3); o += std::to_string(p.Size); o += ",\n";
            key("export_count", 3); o += std::to_string(p.ExportCount); o += ",\n";
            key("export_bundle_count", 3); o += std::to_string(p.BundleCount); o += ",\n";
            key("load_order", 3); o += std::to_string(p.LoadOrder); o += ",\n";
            std::vector<std::string> imports;
            for (uint64_t id : p.Imports) { imports.push_back(Hex16(id)); }
            list("imports", imports, 3);
            key("bulk", 3);
            if (p.Bulk.empty()) { o += "[]\n"; }
            else
            {
                o += "[\n";
                for (size_t k = 0; k < p.Bulk.size(); ++k)
                {
                    o += "    {\n";
                    key("file", 5); Quote(o, p.Bulk[k].File); o += ",\n";
                    key("type", 5); o += std::to_string(p.Bulk[k].Type); o += "\n";
                    o += k + 1 < p.Bulk.size() ? "    },\n" : "    }\n";
                }
                o += "   ]\n";
            }
            o += i + 1 < s.Packages.size() ? "  },\n" : "  }\n";
        }
        o += " ],\n";
    }
    text("built", s.Built);
    text("built_with", s.BuiltWith, false);
    o += "}\n";
    return o;
}

// skin.json read back (the packages' metadata only: Data stays empty). Fields a skin.json does not have keep their
// defaults; "enabled" is off only when it is false.
inline bool ReadSkinJson(const std::string& textIn, SkinInfo& s, std::string& error)
{
    s = SkinInfo{};
    Json root;
    if (!ParseJson(textIn, root, error)) { error = "skin.json does not read: " + error; return false; }
    if (root.Type != Json::Kind::Object) { error = "skin.json is not a JSON object"; return false; }
    const Json* schema = root.Find("schema");
    if (!schema || schema->Type != Json::Kind::String || !StartsWith(schema->Text, "CreateACharacterSkin/"))
    {
        error = "skin.json has no \"schema\": \"CreateACharacterSkin/1\"";
        return false;
    }
    auto text = [&](const char* k, std::string& v) { const Json* j = root.Find(k); if (j && j->Type == Json::Kind::String) { v = j->Text; } };
    auto texts = [&](const char* k, std::vector<std::string>& v) {
        const Json* j = root.Find(k);
        if (!j || j->Type != Json::Kind::Array) { return; }
        for (const Json& item : j->Items) { if (item.Type == Json::Kind::String) { v.push_back(item.Text); } }
    };
    text("name", s.Name);
    text("author", s.Author);
    text("description", s.Description);
    texts("characters", s.Characters);
    text("model", s.Model);
    text("skeleton", s.Skeleton);
    text("family", s.Family);
    if (const Json* j = root.Find("proportions")) { s.Proportions = j->Type == Json::Kind::Bool && j->Boolean; }
    texts("proportion_bones", s.ProportionBones);
    text("voice", s.Voice);
    text("weapon", s.Weapon);
    text("anim_blueprint", s.AnimBlueprint);
    if (const Json* j = root.Find("enabled")) { s.Enabled = !(j->Type == Json::Kind::Bool && !j->Boolean); }
    text("preview", s.Preview);
    text("built", s.Built);
    text("built_with", s.BuiltWith);
    if (!s.Preview.empty() && !SafeRelativePath(s.Preview)) { error = "skin.json's preview \"" + s.Preview + "\" is not a file in the skin folder"; return false; }
    const Json* packages = root.Find("packages");
    if (packages && packages->Type != Json::Kind::Array) { error = "skin.json's \"packages\" is not a list"; return false; }
    if (!packages) { return true; }
    for (size_t i = 0; i < packages->Items.size(); ++i)
    {
        const Json& p = packages->Items[i];
        const std::string where = "skin.json's package " + std::to_string(i);
        if (p.Type != Json::Kind::Object) { error = where + " is not an object"; return false; }
        SkinPackage pkg;
        const Json* name = p.Find("package");
        const Json* file = p.Find("file");
        const Json* size = p.Find("size");
        const Json* exports = p.Find("export_count");
        const Json* bundles = p.Find("export_bundle_count");
        const Json* order = p.Find("load_order");
        if (!name || name->Type != Json::Kind::String || !StartsWith(name->Text, "/Game/")) { error = where + " has no \"package\" under /Game/"; return false; }
        if (!file || file->Type != Json::Kind::String || !StartsWith(file->Text, "Content/") || !EndsWith(file->Text, ".uasset") || !SafeRelativePath(file->Text))
        {
            error = where + " (" + name->Text + ") has no \"file\" Content/....uasset";
            return false;
        }
        pkg.Package = name->Text;
        pkg.File = file->Text;
        uint64_t loadOrder = 0;
        if (!size || !JsonU64(*size, pkg.Size)) { error = where + " (" + pkg.Package + ") has no whole \"size\""; return false; }
        if (!exports || !JsonI32(*exports, pkg.ExportCount) || !bundles || !JsonI32(*bundles, pkg.BundleCount))
        {
            error = where + " (" + pkg.Package + ") has no \"export_count\" or \"export_bundle_count\"";
            return false;
        }
        if (order && (!JsonU64(*order, loadOrder) || loadOrder > 0xFFFFFFFFULL)) { error = where + " (" + pkg.Package + ") has a bad \"load_order\""; return false; }
        pkg.LoadOrder = static_cast<uint32_t>(loadOrder);
        if (const Json* imports = p.Find("imports"))
        {
            if (imports->Type != Json::Kind::Array) { error = where + " (" + pkg.Package + "): \"imports\" is not a list"; return false; }
            for (const Json& id : imports->Items)
            {
                uint64_t v = 0;
                if (!(id.Type == Json::Kind::String && ParseHex64(id.Text, v)) && !(id.Type == Json::Kind::Number && JsonU64(id, v)))
                {
                    error = where + " (" + pkg.Package + ") has an import that is not a package id";
                    return false;
                }
                pkg.Imports.push_back(v);
            }
        }
        if (const Json* bulk = p.Find("bulk"))
        {
            if (bulk->Type != Json::Kind::Array) { error = where + " (" + pkg.Package + "): \"bulk\" is not a list"; return false; }
            for (const Json& b : bulk->Items)
            {
                const Json* bf = b.Type == Json::Kind::Object ? b.Find("file") : nullptr;
                const Json* bt = b.Type == Json::Kind::Object ? b.Find("type") : nullptr;
                uint64_t type = 0;
                if (!bf || bf->Type != Json::Kind::String || !StartsWith(bf->Text, "Content/") || !SafeRelativePath(bf->Text) || !bt || !JsonU64(*bt, type) ||
                    (type != BulkData && type != OptionalBulkData && type != MemoryMappedBulkData) || TypeOfFile(bf->Text) != type)
                {
                    error = where + " (" + pkg.Package + ") has a bulk entry that is not {\"file\": \"Content/...\", \"type\": 3, 4 or 5} of its extension";
                    return false;
                }
                SkinBulk entry;
                entry.File = bf->Text;
                entry.Type = static_cast<uint8_t>(type);
                pkg.Bulk.push_back(std::move(entry));
            }
        }
        s.Packages.push_back(std::move(pkg));
    }
    return true;
}

// ---------------------------------------------------------------------------------------
// The skins container: every skin folder's packages in one ~mods container
// ---------------------------------------------------------------------------------------
struct SkinFolder
{
    std::string Folder;                  // the skin folder's name (skins/<Folder>)
    SkinInfo Info;                       // its skin.json, with every package's Data and bulk Data read in
};

struct CacheResult
{
    bool Ok = false;
    std::string Error;
    Bytes Utoc, Ucas, Pak;
    std::vector<std::string> Report;     // a line per skin folder (and per package left out)
    size_t Packages = 0;
};

// The skins in folder name order (byte order of the UTF-8 names); a skin whose skin.json says "enabled": false is left
// out; a package another skin had first is left out (the first one by folder name wins). Each package goes in as
// Content/<path> under ../../../End/Content/ with its store entry from skin.json (its size from its file, the flags
// above bit 60 kept).
inline CacheResult BuildCache(std::vector<SkinFolder> skins, const std::string& name = CacheName)
{
    CacheResult result;
    std::sort(skins.begin(), skins.end(), [](const SkinFolder& a, const SkinFolder& b) { return a.Folder < b.Folder; });
    std::vector<CacsSound::Container::Package> packages;
    struct BulkRef { size_t Package; uint8_t Type; std::string File; const Bytes* Data; };
    std::vector<std::vector<BulkRef>> bulks;
    std::set<uint64_t> seen;
    for (SkinFolder& skin : skins)
    {
        if (!skin.Info.Enabled)
        {
            result.Report.push_back(skin.Folder + ": off");
            continue;
        }
        size_t taken = 0;
        for (SkinPackage& p : skin.Info.Packages)
        {
            if (!StartsWith(p.Package, "/Game/"))
            {
                result.Error = skin.Folder + ": " + p.Package + " is not under /Game/";
                return result;
            }
            const uint64_t id = CacsSound::Ids::PackageId(p.Package);
            if (!seen.insert(id).second)
            {
                result.Report.push_back(skin.Folder + ": " + p.Package + " is in another skin too, left out");
                continue;
            }
            if (p.Data.empty())
            {
                result.Error = skin.Folder + ": " + p.File + " was not read (empty)";
                return result;
            }
            CacsSound::Container::Package pkg;
            pkg.Path = p.Package;
            pkg.Data = std::move(p.Data);
            pkg.ExportCount = static_cast<uint32_t>(p.ExportCount);
            pkg.BundleCount = static_cast<uint32_t>(p.BundleCount);
            pkg.SizeFlags = p.Size & ~SizeMask;
            pkg.LoadOrder = p.LoadOrder;
            pkg.ImportedPackages = p.Imports;
            packages.push_back(std::move(pkg));
            std::vector<BulkRef> refs;
            for (const SkinBulk& b : p.Bulk)
            {
                if (!StartsWith(b.File, "Content/"))
                {
                    result.Error = skin.Folder + ": " + b.File + " is not under Content/";
                    return result;
                }
                refs.push_back(BulkRef{packages.size() - 1, b.Type, b.File.substr(8), &b.Data});
            }
            bulks.push_back(std::move(refs));
            ++taken;
        }
        result.Report.push_back(skin.Folder + ": " + std::to_string(taken) + " package(s)");
    }
    const uint64_t cid = CacsSound::Container::ContainerId(name);
    const Bytes header = CacsSound::Container::Header(cid, packages);
    std::vector<CacsSound::Container::Chunk> chunks;
    CacsSound::Container::Chunk first;
    first.Id = cid;
    first.Type = ContainerHeaderChunk;
    first.Data = &header;
    chunks.push_back(first);
    for (size_t i = 0; i < packages.size(); ++i)
    {
        CacsSound::Container::Chunk c;
        c.Id = CacsSound::Ids::PackageId(packages[i].Path);
        c.Type = ExportBundleData;
        c.Data = &packages[i].Data;
        c.File = packages[i].Path.substr(6) + ".uasset";
        chunks.push_back(c);
        for (const BulkRef& b : bulks[i])
        {
            CacsSound::Container::Chunk bulk;
            bulk.Id = c.Id;
            bulk.Type = b.Type;
            bulk.Data = b.Data;
            bulk.File = b.File;
            chunks.push_back(bulk);
        }
    }
    CacsSound::Container::Write(name, chunks, result.Utoc, result.Ucas);
    result.Pak = CacsSound::Container::Pak();
    result.Packages = packages.size();
    result.Ok = true;
    return result;
}
} // namespace CacsSkin
