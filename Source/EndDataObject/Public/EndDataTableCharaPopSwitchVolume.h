#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCharaPopSwitchVolume.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCharaPopSwitchVolume : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ShowActorList_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> HideActorList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCharaPopSwitchVolume();
};

