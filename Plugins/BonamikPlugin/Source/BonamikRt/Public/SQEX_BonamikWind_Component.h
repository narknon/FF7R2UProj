#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SQEX_BonamikWind_Desc.h"
#include "SQEX_BonamikWind_Component.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class BONAMIKRT_API USQEX_BonamikWind_Component : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_BonamikWind_Desc mProps;
    
    USQEX_BonamikWind_Component(const FObjectInitializer& ObjectInitializer);

};

