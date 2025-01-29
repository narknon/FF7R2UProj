#pragma once
#include "CoreMinimal.h"
#include "EndMobPrefabAnimationWithLookAtExecuteCommand.h"
#include "EndMobPrefabContactAnimationExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabContactAnimationExecuteCommand : public UEndMobPrefabAnimationWithLookAtExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ForwardLeftMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ForwardRightMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BackLeftMotion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BackRightMotion;
    
    UEndMobPrefabContactAnimationExecuteCommand();

};

