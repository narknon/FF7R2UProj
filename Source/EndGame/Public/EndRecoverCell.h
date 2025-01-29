#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndRecoverCell.generated.h"

class UEndCanvasPanel;
class UEndImage;
class UEndMemberListCellContent;
class UEndRecoverHpPlus;

UCLASS(Blueprintable, EditInlineNew)
class UEndRecoverCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* All_SelectMemberBtn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* BtnDangerBase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* RecoverAll_Base;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberListCellContent* MemberList_CellContent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndRecoverHpPlus* Recover_Hp_Plus;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndRecoverHpPlus* Recover_Mp_Plus;
    
    UEndRecoverCell();

};

