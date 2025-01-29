#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndTinyBroncoExpressionParameter.h"
#include "EndTinyBroncoExpressionParameters.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndTinyBroncoExpressionParameters : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndTinyBroncoExpressionParameter Parameter;
    
    UEndTinyBroncoExpressionParameters();

};

