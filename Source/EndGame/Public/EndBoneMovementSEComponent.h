#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBoneMovementSeSetting.h"
#include "EndBoneMovementSEComponent.generated.h"

class USkeletalMeshComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBoneMovementSEComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBoneMovementSeSetting SeSetting;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* MeshComponent;
    
public:
    UEndBoneMovementSEComponent(const FObjectInitializer& ObjectInitializer);

};

