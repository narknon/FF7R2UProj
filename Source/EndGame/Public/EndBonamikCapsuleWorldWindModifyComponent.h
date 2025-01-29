#pragma once
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "EndBonamikWindComponentInterface.h"
#include "EndBonamikCapsuleWorldWindModifyComponent.generated.h"

class USQEX_BonamikWind_Asset;

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBonamikCapsuleWorldWindModifyComponent : public UCapsuleComponent, public IEndBonamikWindComponentInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEX_BonamikWind_Asset* WindAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Scale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableWorldWind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnabled;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDebugDraw;
    
    UEndBonamikCapsuleWorldWindModifyComponent(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

