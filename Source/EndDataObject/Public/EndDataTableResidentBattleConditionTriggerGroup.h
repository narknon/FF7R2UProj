#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableResidentBattleConditionTriggerGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableResidentBattleConditionTriggerGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BattleConditionTriggerGroupId_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TalkGroupID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableResidentBattleConditionTriggerGroup();
};

