#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldActionDamageReciveInfo.h"
#include "EndFieldActionDamageReciveComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldActionDamageReciveComponent : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldActionDamageReciveInfo> DamageReciveInfo;
    
    UEndFieldActionDamageReciveComponent(const FObjectInitializer& ObjectInitializer);

};

