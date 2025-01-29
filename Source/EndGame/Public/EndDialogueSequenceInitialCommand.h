#pragma once
#include "CoreMinimal.h"
#include "EndDialogueSequenceInitialCommand.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueSequenceInitialCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GenerateId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CommandType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> StringArguments;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> IntegerArguments;
    
    FEndDialogueSequenceInitialCommand();
};

