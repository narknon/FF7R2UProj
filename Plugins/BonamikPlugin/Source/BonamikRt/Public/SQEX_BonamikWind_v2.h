#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ESQEX_Bonamik_WindOwnerType.h"
#include "SQEX_BonamikWind_v2.generated.h"

UCLASS(Blueprintable, Transient)
class BONAMIKRT_API USQEX_BonamikWind_v2 : public UObject {
    GENERATED_BODY()
public:
    USQEX_BonamikWind_v2();

    UFUNCTION(BlueprintCallable)
    static void EnableByOwnerType(bool bEnable, TEnumAsByte<ESQEX_Bonamik_WindOwnerType> OwnerType);
    
};

