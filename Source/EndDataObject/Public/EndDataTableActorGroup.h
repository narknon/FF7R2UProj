#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableActorGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableActorGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ActorList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableActorGroup();
};

