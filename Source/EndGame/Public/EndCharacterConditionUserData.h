#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndCharacterConditionUserData.generated.h"

class USkeletalMesh;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndCharacterConditionUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<USkeletalMesh> ConditionModel;
    
    UEndCharacterConditionUserData();

};

