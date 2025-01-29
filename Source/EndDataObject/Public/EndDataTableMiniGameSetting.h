#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableMiniGameSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableMiniGameSetting : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 UseSoundLayer;
    
public:
    ENDDATAOBJECT_API FEndDataTableMiniGameSetting();
};

