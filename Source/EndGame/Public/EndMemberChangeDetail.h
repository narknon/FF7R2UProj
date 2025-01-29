#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMemberChangeDetail.generated.h"

class UEndCanvasPanel;
class UEndMemberChangeBtn;
class UEndMemberChangeStatus;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberChangeDetail : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeBtn* member_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeStatus* Status_1_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeStatus* Status_1_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeBtn* member_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeStatus* Status_2_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberChangeStatus* Status_2_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Info;
    
    UEndMemberChangeDetail();

};

