#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBikeModelInfo.h"
#include "Templates/SubclassOf.h"
#include "EndBikeCharacterComponent.generated.h"

class AEndBikeAIController;
class AEndBikeControllerBase;
class AEndBikePlayerControllerBase;
class UEndBikeMovementSettingBase;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeCharacterComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeModelInfo BikeModelInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndBikeMovementSettingBase* BikeMovementSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndBikeControllerBase* CurrentBikeController;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndBikePlayerControllerBase> BikePlayerControllerClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<TSubclassOf<AEndBikeAIController>> BikeAIControllerClasses;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndBikeAIController* BikeAIController;
    
    UEndBikeCharacterComponent(const FObjectInitializer& ObjectInitializer);

};

