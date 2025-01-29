#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EndPhysicsTriggerBox.generated.h"

UCLASS(Blueprintable)
class AEndPhysicsTriggerBox : public ATriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TriggerNamesOnPhysicsObjectBroken;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOnlyReactToUnbreakablePhysicsObjects;
    
public:
    AEndPhysicsTriggerBox(const FObjectInitializer& ObjectInitializer);

};

