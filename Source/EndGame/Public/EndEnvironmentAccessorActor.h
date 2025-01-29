#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndEnvironmentAccessorActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndEnvironmentAccessorActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, AActor*> EnvironmentMap;
    
    AEndEnvironmentAccessorActor(const FObjectInitializer& ObjectInitializer);

};

