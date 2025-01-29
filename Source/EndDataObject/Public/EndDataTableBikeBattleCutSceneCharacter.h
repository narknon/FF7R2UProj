#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeBattleCutSceneCharacter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeBattleCutSceneCharacter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ViecleCharaName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> RiderCharaNameList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeBattleCutSceneCharacter();
};

