#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "IconInfo.h"
#include "EndNewSenseIconInfo.generated.h"

class UEndCanvasPanel;
class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewSenseIconInfo : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* Nut_IconInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* List1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* List2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FIconInfo> List1Info;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FIconInfo> List2Info;
    
    UEndNewSenseIconInfo();

};

