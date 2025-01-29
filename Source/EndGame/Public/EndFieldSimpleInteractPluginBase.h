#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndFieldSimpleInteractPluginBase.generated.h"

class UEndFieldSimpleInteractPluginBase;

UCLASS(Abstract, Blueprintable)
class UEndFieldSimpleInteractPluginBase : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNoCompleteSkipAfterPlugin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCompleteAndDoParentComplete;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldSimpleInteractPluginBase*> PluginChildren;
    
    UEndFieldSimpleInteractPluginBase();

};

