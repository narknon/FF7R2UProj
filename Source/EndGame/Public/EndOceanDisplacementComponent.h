#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndOceanDisplacementComponent.generated.h"

class UEndMaterialAnimateTimeUnnormalizedComponent;
class UEndOceanDisplacementDataAsset;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndOceanDisplacementComponent : public UActorComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndOceanDisplacementDataAsset* OceanDisplacementDataAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UEndMaterialAnimateTimeUnnormalizedComponent* OceanMaterialAnimateTimeComponent;
    
public:
    UEndOceanDisplacementComponent(const FObjectInitializer& ObjectInitializer);

};

