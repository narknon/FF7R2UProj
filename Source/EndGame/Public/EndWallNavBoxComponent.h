#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndWallNavBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndWallNavBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 BoxID;
    
    UEndWallNavBoxComponent(const FObjectInitializer& ObjectInitializer);

};

