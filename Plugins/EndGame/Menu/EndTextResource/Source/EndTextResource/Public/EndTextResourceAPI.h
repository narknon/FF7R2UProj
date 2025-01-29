#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndTextResourceInfo.h"
#include "EndTextResourceAPI.generated.h"

UCLASS(Blueprintable)
class UEndTextResourceAPI : public UObject {
    GENERATED_BODY()
public:
    UEndTextResourceAPI();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString GetTextResourceText(const FString& InTextId, const FString& InLanguage);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FEndTextResourceInfo GetTextResourceInfo(const FString& InTextId, const FString& InLanguage);
    
};

