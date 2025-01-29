#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCardGame.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCardGame : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName WonStoryFlagID;
    
public:
    ENDDATAOBJECT_API FEndDataTableCardGame();
};

