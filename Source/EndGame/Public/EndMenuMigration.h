#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMenuMigration.generated.h"

class UWidget;

UCLASS(Blueprintable)
class UEndMenuMigration : public UObject {
    GENERATED_BODY()
public:
    UEndMenuMigration();

    UFUNCTION(BlueprintCallable)
    static void SetTextToTextBlock(UWidget* InTextBlock, FText InText);
    
    UFUNCTION(BlueprintCallable)
    static FText GetTextFromTextBlock(UWidget* InTextBlock);
    
};

