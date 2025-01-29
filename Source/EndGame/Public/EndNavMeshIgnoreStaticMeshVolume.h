#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "Templates/SubclassOf.h"
#include "EndNavMeshIgnoreStaticMeshVolume.generated.h"

class UNavArea;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndNavMeshIgnoreStaticMeshVolume : public AActor, public INavRelevantInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UNavArea> AreaClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UStaticMeshComponent* StaticMeshComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UStaticMesh* StaticMesh;
    
public:
    AEndNavMeshIgnoreStaticMeshVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

