#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EndMenuSkillTreeColorSetting.h"
#include "EndUserWidget.h"
#include "EndNewSkillTreeMenu.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSkillTreeMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EPlayerType, FEndMenuSkillTreeColorSetting> ColorSettings;
    
    UEndNewSkillTreeMenu();

};

