#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableFavoritePointFlag.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableFavoritePointFlag : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPlayerTable_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> StoryFlag_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableFavoritePointFlag();
};

