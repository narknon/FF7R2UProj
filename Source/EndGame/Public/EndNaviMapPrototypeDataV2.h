#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndNaviMapLocationPrototypeDataV2.h"
#include "EndNaviMapPrototypeDataV2.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndNaviMapPrototypeDataV2 : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndNaviMapLocationPrototypeDataV2> Locations;
    
    UEndNaviMapPrototypeDataV2();

};

