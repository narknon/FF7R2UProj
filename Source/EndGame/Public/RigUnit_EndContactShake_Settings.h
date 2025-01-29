#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndContactShake_Item.h"
#include "RigUnit_EndContactShake_Settings.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndContactShake_Settings {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FRigUnit_EndContactShake_Item> Items;
    
    ENDGAME_API FRigUnit_EndContactShake_Settings();
};

