#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EndDataTableConfig.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableConfig : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Comment;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString CommentEN;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Status;
    
    ENDGAME_API FEndDataTableConfig();
};

