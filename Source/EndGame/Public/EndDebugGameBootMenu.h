#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugBootMenuShowListBoxDelegate.h"
#include "EndDebugGameBootMenu.generated.h"

UCLASS(Blueprintable)
class AEndDebugGameBootMenu : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FDebugBootMenuShowListBox CallShowDialogEvent;
    
    AEndDebugGameBootMenu(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void OnCompleteShowDebugListBox(const FString& SelectString);
    
};

