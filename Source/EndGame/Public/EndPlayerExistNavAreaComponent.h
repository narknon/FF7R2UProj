#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndPlayerExistNavAreaComponent.generated.h"

class AActor;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndPlayerExistNavAreaComponent : public UActorComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, AActor*> NavModifierMap;
    
public:
    UEndPlayerExistNavAreaComponent(const FObjectInitializer& ObjectInitializer);

};

