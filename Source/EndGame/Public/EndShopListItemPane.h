#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndShopListItemPane.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndShopListItemPane : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor _FoucsedColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor _UnFoucsedColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor _UnSelectedColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSoftObjectPath> ChadolyShopAreaMappings;
    
    UEndShopListItemPane();

    UFUNCTION(BlueprintCallable)
    void OnShopAreaTubListIconSet(UWidget* ItemWidget, int32 ItemIndex);
    
};

