#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBodySubCollisionSetting.h"
#include "EndBodySubCollisionSettingComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBodySubCollisionSettingComponent : public UActorComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBodySubCollisionSetting> BodySubCollisionSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BehaviorModeLabel_Neutral;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BehaviorModeLabel_Battle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BehaviorModeLabel_Caution;
    
public:
    UEndBodySubCollisionSettingComponent(const FObjectInitializer& ObjectInitializer);

};

