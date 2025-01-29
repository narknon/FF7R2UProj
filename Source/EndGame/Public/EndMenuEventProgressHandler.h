#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuEventProgressHandler.generated.h"

UCLASS(Blueprintable)
class UEndMenuEventProgressHandler : public UObject {
    GENERATED_BODY()
public:
    UEndMenuEventProgressHandler();

    UFUNCTION(BlueprintCallable)
    FVector2D OnListMissionMeasureItem(int32 ItemIndex);
    
};

