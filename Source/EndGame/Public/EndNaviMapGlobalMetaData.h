#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapMetaDataActorClass.h"
#include "EndNaviMapMetaDataIcon.h"
#include "EndNaviMapGlobalMetaData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapGlobalMetaData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapMetaDataActorClass> actor_classes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapMetaDataIcon> icons;
    
    FEndNaviMapGlobalMetaData();
};

