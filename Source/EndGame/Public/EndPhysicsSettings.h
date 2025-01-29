#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCollisionDefaultSettings.h"
#include "EndPhysicsObjectsSettings.h"
#include "EndPhysicsSettings.generated.h"

UCLASS(Blueprintable, DefaultConfig, Config=Game)
class ENDGAME_API UEndPhysicsSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndPhysicsObjectsSettings Objects;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCollisionDefaultSettings CollisionDefaultSettings;
    
    UEndPhysicsSettings();

};

