#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndTopListWindow.generated.h"

class UEndVirtualScrollBox;

UCLASS(Blueprintable, EditInlineNew)
class UEndTopListWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVirtualScrollBox* ScrollBox;
    
    UEndTopListWindow();

};

