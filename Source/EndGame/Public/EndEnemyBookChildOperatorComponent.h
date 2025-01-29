#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndEnemyBookChildOperatorComponent.generated.h"

class UAnimSequence;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndEnemyBookChildOperatorComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimSequence* AnimSequence;
    
    UEndEnemyBookChildOperatorComponent(const FObjectInitializer& ObjectInitializer);

};

