#pragma once
#include "CoreMinimal.h"
#include "EndCharaIDBranch.generated.h"

USTRUCT(BlueprintType)
struct FEndCharaIDBranch {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CharaID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    ENDGAME_API FEndCharaIDBranch();
};

