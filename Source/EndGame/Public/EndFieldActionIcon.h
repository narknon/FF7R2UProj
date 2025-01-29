#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndUserWidget.h"
#include "EndFieldActionIcon.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldActionIcon : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D _BasePosY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D _PaddingY;
    
    UEndFieldActionIcon();

};

