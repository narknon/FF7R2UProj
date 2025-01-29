#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractStateSetting.generated.h"

class UEndFieldSimpleInteractPluginBase;

USTRUCT(BlueprintType)
struct FEndFieldSimpleInteractStateSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StateName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldSimpleInteractPluginBase*> FieldActorPluginArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldSimpleInteractPluginBase*> PlayerPluginArray;
    
    ENDGAME_API FEndFieldSimpleInteractStateSetting();
};

