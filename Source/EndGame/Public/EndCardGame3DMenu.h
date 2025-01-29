#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndCardGame3DMenu.generated.h"

class UEndCardGameCardPane;

UCLASS(Blueprintable, EditInlineNew)
class UEndCardGame3DMenu : public UEndUserWidget {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndCardGameCardPane*> _DeckCard;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndCardGameCardPane*> _DeckCardDummy;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndCardGameCardPane*> _DeckCardPool;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCardGameCardPane* _PlacementCard;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* _PlacementCursor;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* _PlacementFrame;
    
public:
    UEndCardGame3DMenu();

};

