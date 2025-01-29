#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EWeaponSlot.h"
#include "EndAnimNotifyAttachEnvironmentSkeletalMesh.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class UEndAnimNotifyAttachEnvironmentSkeletalMesh : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AccessorID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableCollision;
    
    UEndAnimNotifyAttachEnvironmentSkeletalMesh();

};

