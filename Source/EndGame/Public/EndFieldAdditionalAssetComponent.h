#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldAdditionalAssetComponent.generated.h"

class USoundBase;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAdditionalAssetComponent : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* SoundBank;
    
    UEndFieldAdditionalAssetComponent(const FObjectInitializer& ObjectInitializer);

};

