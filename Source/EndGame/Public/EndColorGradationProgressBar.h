#pragma once
#include "CoreMinimal.h"
#include "EndPercentAndColorPair.h"
#include "EndProgressBar.h"
#include "EndColorGradationProgressBar.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndColorGradationProgressBar : public UEndProgressBar {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndPercentAndColorPair> FillColorAndOpacityList;
    
    UEndColorGradationProgressBar();

};

