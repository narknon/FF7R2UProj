#pragma once
#include "CoreMinimal.h"
#include "MemoryMappedAsset.h"
#include "EndNavMeshDataChunkAssetOld.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndNavMeshDataChunkAssetOld : public UMemoryMappedAsset {
    GENERATED_BODY()
public:
    UEndNavMeshDataChunkAssetOld();

};

