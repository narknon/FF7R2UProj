#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCardGameOpponentDeck.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCardGameOpponentDeck : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Thumbnail;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> cardID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCardGameOpponentDeck();
};

