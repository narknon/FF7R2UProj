#pragma once
#include "CoreMinimal.h"
#include "EEndMobPrefabMessage.h"
#include "EndMobPrefabExecuteCommand.h"
#include "EndMobPrefabEventMessageExecuteCommand.generated.h"

UCLASS(Blueprintable)
class UEndMobPrefabEventMessageExecuteCommand : public UEndMobPrefabExecuteCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMobPrefabMessage Message;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> IntegerContexts;
    
    UEndMobPrefabEventMessageExecuteCommand();

};

