#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndAssetEndObjectJson.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndAssetEndObjectJson : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MainSceneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, FString> Scenes;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint64, FString> Nodes;
    
    UEndAssetEndObjectJson();

};

