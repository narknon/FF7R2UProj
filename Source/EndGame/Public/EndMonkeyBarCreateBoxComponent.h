#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndMonkeyBarCreateBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndMonkeyBarCreateBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 BoxID;
    
    UEndMonkeyBarCreateBoxComponent(const FObjectInitializer& ObjectInitializer);

};

