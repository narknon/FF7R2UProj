#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMenuBattleFriendStatusPane.generated.h"

class UWidget;

UCLASS(Blueprintable, EditInlineNew)
class UEndMenuBattleFriendStatusPane : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _FriendPaneShears;
    
    UEndMenuBattleFriendStatusPane();

    UFUNCTION(BlueprintCallable)
    void OnFriendStatusCell(UWidget* ItemWidget, int32 ItemIndex);
    
};

