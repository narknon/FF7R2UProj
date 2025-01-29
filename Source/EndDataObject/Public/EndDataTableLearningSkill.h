#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableLearningSkill.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableLearningSkill : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Probability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 EnemyAbilityMateriaFlag;
    
public:
    ENDDATAOBJECT_API FEndDataTableLearningSkill();
};

