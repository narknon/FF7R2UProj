#pragma once
#include "CoreMinimal.h"
#include "MemoryMappedAsset.h"
#include "EndStreamableAssetPump.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndStreamableAssetPump : public UMemoryMappedAsset {
    GENERATED_BODY()
public:
    UEndStreamableAssetPump();

};

