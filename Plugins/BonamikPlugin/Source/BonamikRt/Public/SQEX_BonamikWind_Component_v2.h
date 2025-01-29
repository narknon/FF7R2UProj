#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/SceneComponent.h"
#include "ESQEX_Bonamik_WindAreaType.h"
#include "SQEX_BonamikWind_Component_v2.generated.h"

class USQEX_BonamikWindDesc_v2;
class USQEX_BonamikWind_v2;

UCLASS(Blueprintable, CollapseCategories, Deprecated, NotPlaceable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UDEPRECATED_SQEX_BonamikWind_Component_v2 : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikWindDesc_v2* m_BonamikWindDesc;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_Bonamik_WindAreaType> m_BonamikWindAreaType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_BonamikWindGlobalAddition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_BonamikWindBoxAreaSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_BonamikWindBoxAreaHalfSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BonamikWindSphereAreaRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BonamikWindAreaMargin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_BonamikWindAbsoluteDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BonamikWindDirectionYaw;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BonamikWindDirectionPitch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEX_BonamikWind_v2* m_BonamikWind;
    
    UDEPRECATED_SQEX_BonamikWind_Component_v2(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetWindScale(float Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetWindScale() const;
    
    UFUNCTION(BlueprintCallable)
    void Enable(bool Value);
    
};

