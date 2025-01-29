#pragma once
#include "CoreMinimal.h"
#include "EndFieldActorAnimUnit.h"
#include "EndFieldAnimSettingBase.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldAnimSettingBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldActorAnimUnit> AnimationUnits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsLoop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastAnimIsKeep;
    
    ENDGAME_API FEndFieldAnimSettingBase();
};

