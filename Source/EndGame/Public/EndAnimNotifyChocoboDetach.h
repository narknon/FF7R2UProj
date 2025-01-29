#pragma once
#include "CoreMinimal.h"
#include "EndAnimNotifyVehicleDetachBase.h"
#include "EndAnimNotifyChocoboDetach.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyChocoboDetach : public UEndAnimNotifyVehicleDetachBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bJumpOnDetatch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float JumpVelocityXY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float JumpVelocityZ;
    
    UEndAnimNotifyChocoboDetach();

};

