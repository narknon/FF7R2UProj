#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBoxing3DBattlerEnemyCombo.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBoxing3DBattlerEnemyCombo : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> ComboPunch_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBoxing3DBattlerEnemyCombo();
};

