#pragma once
#include "CoreMinimal.h"
#include "MemoryMappedAsset.h"
#include "EndNavMeshDataChunkAsset.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndNavMeshDataChunkAsset : public UMemoryMappedAsset {
    GENERATED_BODY()
public:
    UEndNavMeshDataChunkAsset();

};

