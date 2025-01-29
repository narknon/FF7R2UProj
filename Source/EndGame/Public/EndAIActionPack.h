#pragma once
#include "CoreMinimal.h"
#include "EndAIActionPackBase.h"
#include "EndAIActionPackInfo.h"
#include "EndAIActionPack.generated.h"

UCLASS(Blueprintable)
class UEndAIActionPack : public UEndAIActionPackBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIActionPackInfo> AIActionPackInfoList;
    
    UEndAIActionPack();

};

