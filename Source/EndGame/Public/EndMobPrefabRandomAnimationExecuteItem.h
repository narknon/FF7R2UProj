#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabRandomAnimationExecuteItem.generated.h"

USTRUCT(BlueprintType)
struct FEndMobPrefabRandomAnimationExecuteItem {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Motion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bAllowMotionCancel;
    
    ENDGAME_API FEndMobPrefabRandomAnimationExecuteItem();
};

