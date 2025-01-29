#pragma once
#include "CoreMinimal.h"
#include "IpNetDriver.h"
#include "NetDriverEOS.generated.h"

UCLASS(Blueprintable, NonTransient, Config=Engine)
class ONLINESUBSYSTEMEOS_API UNetDriverEOS : public UIpNetDriver {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIsPassthrough;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIsUsingP2PSockets;
    
    UNetDriverEOS();

};

