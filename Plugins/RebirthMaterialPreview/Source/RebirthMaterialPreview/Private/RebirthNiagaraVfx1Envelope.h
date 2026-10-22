// Load-only proposal: not a replacement serializer until the owning adapter is reviewed.
// Call ONLY after FNiagaraVariableBase::Serialize has consumed Name/TypeDefinition.
// Non-VFX1 returns with the archive unchanged so the exact original serializer can run.
#pragma once
#include "CoreMinimal.h"
#include "Serialization/Archive.h"

namespace RebirthNiagaraVfx1
{
enum class EReadResult : uint8 { NotVfx1, Loaded, Refused };
struct FEnvelope
{
    uint32 Magic = 0;
    uint32 OpaqueTypeHash = 0; // Preserved only. No type interpretation is claimed.
    uint32 FormatWord = 0;
    uint32 OpaqueHeaderWord = 0;
    TArray<uint8> VariableData;
};

// This must not be used to save: the native TypeDefinition was empty in the proven
// fixture and neither the opaque hash nor its type semantics have been recovered.
// An owning adapter must prohibit saving/cooking any package containing Loaded
// envelopes, until an exact lossless write path and type mapping are implemented.
inline EReadResult TryReadLoadOnlyEnvelope(FArchive& Ar, FEnvelope& Out)
{
    if (!Ar.IsLoading() || Ar.IsSaving() || Ar.IsError())
    {
        return EReadResult::NotVfx1;
    }
    // UScriptStruct supplies a temporary structured-archive proxy. Its
    // TotalSize() asserts; GetCacheableArchive is the public binary unwrap API.
    // Keep reads on Ar, use its same-data underlying archive ONLY for bounds.
    FArchive* BoundsArchive = Ar.GetCacheableArchive();
    if (!BoundsArchive || Ar.IsTextFormat() || BoundsArchive->IsTextFormat())
    {
        return EReadResult::NotVfx1;
    }
    const int64 Start = Ar.Tell();
    if (BoundsArchive->Tell() != Start)
    {
        Ar.SetError();
        return EReadResult::Refused;
    }
    const int64 Total = BoundsArchive->TotalSize();
    if (Start < 0 || Total < Start || Total - Start < int64(sizeof(uint32)))
    {
        return EReadResult::NotVfx1;
    }
    uint32 Magic = 0;
    Ar << Magic;
    if (Magic != 0x56465831u)
    {
        Ar.Seek(Start);
        return EReadResult::NotVfx1;
    }
    // Proven envelope: FOUR uint32 header words then byte-array count and bytes.
    // Nonempty original Cloud variables prove there is NO trailing int32.
    // Never allocate before checking bounds.
    if (Total - Start < 20)
    {
        Ar.SetError();
        return EReadResult::Refused;
    }
    FEnvelope Parsed;
    Parsed.Magic = Magic;
    Ar << Parsed.OpaqueTypeHash;
    Ar << Parsed.FormatWord;
    Ar << Parsed.OpaqueHeaderWord;
    if (Parsed.FormatWord != 0x00020001u || Parsed.OpaqueHeaderWord != 0u)
    {
        Ar.SetError();
        return EReadResult::Refused;
    }
    int32 Count = 0;
    Ar << Count;
    const int64 DataStart = Ar.Tell();
    constexpr int32 MaximumVariableBytes = 1024 * 1024;
    if (Ar.IsError() || Count < 0 || Count > MaximumVariableBytes ||
        DataStart != Start + 20 || DataStart > Total ||
        int64(Count) > Total - DataStart)
    {
        Ar.SetError();
        return EReadResult::Refused;
    }
    Parsed.VariableData.SetNumUninitialized(Count);
    if (Count > 0)
    {
        Ar.Serialize(Parsed.VariableData.GetData(), Count);
    }
    if (Ar.IsError() || Ar.Tell() != Start + 20 + int64(Count))
    {
        Ar.SetError();
        return EReadResult::Refused;
    }
    Out = MoveTemp(Parsed);
    return EReadResult::Loaded;
}
}
