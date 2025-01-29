#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMobPrefabExecuteCommand.h"
#include "EndMobPrefabRandomAnimationExecuteItem.h"
#include "EndMobPrefabRandomAnimationExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabRandomAnimationExecuteCommand : public UEndMobPrefabExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMobPrefabRandomAnimationExecuteItem> Items;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLooping;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Layer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceBaseMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ReplaceBaseLookAtTarget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D CompleteTimeRange;
    
    UEndMobPrefabRandomAnimationExecuteCommand();

};

