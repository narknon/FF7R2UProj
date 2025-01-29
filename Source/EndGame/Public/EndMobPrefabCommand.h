#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndMobPrefabCommand.generated.h"

UCLASS(Abstract, Blueprintable)
class UEndMobPrefabCommand : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 RegistryIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 commandID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ChainCommandId;
    
    UEndMobPrefabCommand();

};

