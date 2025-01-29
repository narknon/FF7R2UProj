#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCutSceneChangeEquipList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCutSceneChangeEquipList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetCharacterName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AfterWeaponID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BeforeWeaponIDArray_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCutSceneChangeEquipList();
};

