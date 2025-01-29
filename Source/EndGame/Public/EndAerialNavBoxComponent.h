#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndAerialNavBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAerialNavBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 BoxID;
    
    UEndAerialNavBoxComponent(const FObjectInitializer& ObjectInitializer);

};

