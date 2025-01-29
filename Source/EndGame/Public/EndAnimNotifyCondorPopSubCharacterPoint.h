#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndAnimNotifyCondorPopSubCharacterPoint.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimNotifyCondorPopSubCharacterPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Socket;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Offset;
    
    ENDGAME_API FEndAnimNotifyCondorPopSubCharacterPoint();
};

