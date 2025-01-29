#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BonamikWorldInterface_v2.h"
#include "SQEX_Bonamik_Component_v2.generated.h"

class UCharacterMovementComponent;
class USQEX_BonamikAsset_v2;
class USkeletalMeshComponent;

UCLASS(Blueprintable, Deprecated, NotPlaceable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class BONAMIKRT_API UDEPRECATED_SQEX_Bonamik_Component_v2 : public USceneComponent, public IBonamikWorldInterface_v2 {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bHasSkeletalMeshSkippedTransforms;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikAsset_v2* m_BonamikAsset;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* SkeletalMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UCharacterMovementComponent* CharacterMovementComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool m_BonamikEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool m_BonamikAutoDisable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool bAccurateBoundsUpdate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    int32 PreRollStepOnResume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float PrevScreenSize;
    
public:
    UDEPRECATED_SQEX_Bonamik_Component_v2(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

