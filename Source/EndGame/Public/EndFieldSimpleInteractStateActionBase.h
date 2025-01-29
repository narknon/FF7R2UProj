#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "EndFieldSimpleInteractStateActionBase.generated.h"

class UEndFieldSimpleInteractStateSettingObject;

UCLASS(Abstract, Blueprintable)
class UEndFieldSimpleInteractStateActionBase : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HubId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndFieldSimpleInteractStateSettingObject> StateSettingObjectClass;
    
    UEndFieldSimpleInteractStateActionBase();

};

