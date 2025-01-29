#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndSBScooterExpressionParameter.h"
#include "EndSBScooterExpressionParameters.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndSBScooterExpressionParameters : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSBScooterExpressionParameter Parameter;
    
    UEndSBScooterExpressionParameters();

};

