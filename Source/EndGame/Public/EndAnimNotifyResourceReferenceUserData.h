#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetUserData.h"
#include "EndAnimNotifyResourceReferenceUserData.generated.h"

class UObject;

UCLASS(Blueprintable, EditInlineNew)
class ENDGAME_API UEndAnimNotifyResourceReferenceUserData : public UAssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, UObject*> Assets;
    
    UEndAnimNotifyResourceReferenceUserData();

};

