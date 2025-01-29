#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndTopContent.generated.h"

class UEndCanvasPanel;
class UEndPartyLevelExperienceWindow;
class UEndPlayerLevelWindow;
class UEndTopListWindow;

UCLASS(Blueprintable, EditInlineNew)
class UEndTopContent : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTopListWindow* LeftMenu_Top;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLevelWindow* PlayerLevel_00;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLevelWindow* PlayerLevel_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPlayerLevelWindow* PlayerLevel_02;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPartyLevelExperienceWindow* PartyLevel;
    
    UEndTopContent();

};

