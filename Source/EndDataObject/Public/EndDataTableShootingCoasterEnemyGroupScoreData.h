#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableShootingCoasterEnemyGroupScoreData.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableShootingCoasterEnemyGroupScoreData : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupCoasterNormalScore;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupCoasterHardScore;
    
public:
    ENDDATAOBJECT_API FEndDataTableShootingCoasterEnemyGroupScoreData();
};

