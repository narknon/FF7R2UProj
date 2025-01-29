#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndBattleLinkageIcon.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndBattleLinkageIcon : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool _SetBurstSpace;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool _SetBurstComma;
    
    UEndBattleLinkageIcon();

};

