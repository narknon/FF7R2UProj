#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCraftAreaInfo.generated.h"

class UEndCanvasPanel;
class UEndCraftAreaInfoCell;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndCraftAreaInfo : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_3;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_4;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_5;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_6;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_7;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCraftAreaInfoCell* AreaInfo_8;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Alarm;
    
    UEndCraftAreaInfo();

};

