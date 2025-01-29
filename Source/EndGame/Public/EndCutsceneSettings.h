#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCutsceneBudgetSettings.h"
#include "EndCutsceneSettings.generated.h"

UCLASS(Blueprintable, DefaultConfig, Config=Game)
class ENDGAME_API UEndCutsceneSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCutsceneBudgetSettings BudgetSettings;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CutSceneFstopBooster;
    
    UEndCutsceneSettings();

};

