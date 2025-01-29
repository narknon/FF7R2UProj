#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EDebugMessageShowType.h"
#include "EndDataTableDebugMessage.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableDebugMessage : public FTableRowBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Comment;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EDebugMessageShowType ShowType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Message;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, FString> UserExpandVariables;
    
    ENDGAME_API FEndDataTableDebugMessage();
};

