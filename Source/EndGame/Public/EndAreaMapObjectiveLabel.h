#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndAreaMapObjectiveLabel.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndAreaMapObjectiveLabel : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor MainStoryColor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FLinearColor SubStoryColor;
    
    UEndAreaMapObjectiveLabel();

};

