#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "EndPathWayBoxActor.generated.h"

class UBoxComponent;
class UEndNavModifierComponent;

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndPathWayBoxActor : public AActor, public INavRelevantInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector PathWayDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* PathWayBoxComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* PathWayModifierVolume;
    
public:
    AEndPathWayBoxActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

