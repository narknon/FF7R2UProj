#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndFlowMapAnimationSettings.h"
#include "EndFlowMapAnimationUserData.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndFlowMapAnimationUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFlowMapAnimationSettings FlowMapAnimationSettings;
    
    UEndFlowMapAnimationUserData();

};

