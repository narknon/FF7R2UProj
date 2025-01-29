#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "Templates/SubclassOf.h"
#include "EndNavMeshIgnoreBoxVolume.generated.h"

class UBoxComponent;
class UEndNavModifierComponent;
class UNavArea;

UCLASS(Blueprintable, MinimalAPI)
class AEndNavMeshIgnoreBoxVolume : public AActor, public INavRelevantInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UNavArea> AreaClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
public:
    AEndNavMeshIgnoreBoxVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

