#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/AssetUserData.h"
#include "EndChocoboPartsAssetUserData.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndChocoboPartsAssetUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FColor> ColorPreset0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FColor> ColorPreset1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FColor> ColorPreset2;
    
    UEndChocoboPartsAssetUserData();

};

