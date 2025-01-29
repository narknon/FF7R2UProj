#pragma once
#include "CoreMinimal.h"
#include "EndBodySubCollisionData.h"
#include "EndBodySubCollisionSetting.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBodySubCollisionSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LabelName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBodySubCollisionData> Shapes;
    
    FEndBodySubCollisionSetting();
};

