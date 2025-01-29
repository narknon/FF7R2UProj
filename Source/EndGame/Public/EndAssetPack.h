#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/Interface_AssetUserData.h"
#include "EndAssetPack.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndAssetPack : public UObject, public IInterface_AssetUserData {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> AssetUserData;
    
public:
    UEndAssetPack();


    // Fix for true pure virtual functions not being implemented
};

