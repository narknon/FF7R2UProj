#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBattleBreakableAttachData.h"
#include "EndBattleBreakableCharacterComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleBreakableCharacterComponent : public UActorComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBattleBreakableAttachData> BreakableAttachDataList;
    
public:
    UEndBattleBreakableCharacterComponent(const FObjectInitializer& ObjectInitializer);

};

