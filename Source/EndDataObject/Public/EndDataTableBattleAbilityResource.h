#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleAbilityResource.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleAbilityResource : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ContentsSoundSE;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ContentsEffect;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleAbilityResource();
};

