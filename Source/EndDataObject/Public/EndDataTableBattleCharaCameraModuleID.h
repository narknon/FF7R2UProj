#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleCharaCameraModuleID.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleCharaCameraModuleID : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CameraModuleID;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleCharaCameraModuleID();
};

