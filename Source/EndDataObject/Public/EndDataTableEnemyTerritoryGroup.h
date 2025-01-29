#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyTerritoryGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyTerritoryGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EnemyTerritory_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyTerritoryGroup();
};

