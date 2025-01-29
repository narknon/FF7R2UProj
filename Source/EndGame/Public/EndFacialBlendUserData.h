#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndFacialBlendUserData.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndFacialBlendUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BlendIgnoreBoneNames;
    
    UEndFacialBlendUserData();

};

