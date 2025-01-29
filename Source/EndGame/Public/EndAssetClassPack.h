#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/Interface_AssetUserData.h"
#include "EndAssetClassPack.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndAssetClassPack : public UObject, public IInterface_AssetUserData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UClass*> AssetUserData;
    
    UEndAssetClassPack();


    // Fix for true pure virtual functions not being implemented
};

