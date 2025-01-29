#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectBattleAbilityAccessor.h"
#include "Components/ActorComponent.h"
#include "EndBattleTalkCharacterComponent.generated.h"

class AEndCharacter;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleTalkCharacterComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndBattleTalkCharacterComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
    bool OnNotifyWithAbility(const FName& AnimName, const FName& SoundName, AEndCharacter* OwnerChara, AEndCharacter* targetChara, const FName& AbilityId, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility, bool bFinishBlow) const;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
    bool OnNotify(const FName& AnimName, const FName& SoundName, AEndCharacter* OwnerChara) const;
    
};

