#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMemberListCell.generated.h"

class UEndBattleLeaderMark;
class UEndCanvasPanel;
class UEndCoreListNew;
class UEndImage;
class UEndMemberListCellContent;
class UEndProgressBar;
class UEndWeaponStatusSpAutoIcon;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberListCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberListCellContent* MemberList_CellContent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBattleLeaderMark* BattleLeaderMarkIcon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_Core;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCoreListNew* Core_List;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWeaponStatusSpAutoIcon* SpAutoIcon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Pnl_AbilityExp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* AbilityExp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndProgressBar* Gauge_AbilityExp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_AbilityClear;
    
    UEndMemberListCell();

};

