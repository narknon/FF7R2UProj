#pragma once
#include "CoreMinimal.h"
#include "NextStateChange.h"
#include "StateConditionParam.h"
#include "EndObject_StateChange.generated.h"

USTRUCT(BlueprintType)
struct FEndObject_StateChange {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Comment;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 UniqueIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 OwnerUniqueIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EnterActions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FStateConditionParam> StateConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FNextStateChange> NextStateTriggers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Status;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LoopAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LoopEffect;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StringArg[16];
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 IntegerArg[16];
    
    ENDGAME_API FEndObject_StateChange();
};

