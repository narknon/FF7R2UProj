#pragma once
#include "CoreMinimal.h"
#include "EndSkillCameraDitherFadeRelatedActorData.generated.h"

USTRUCT(BlueprintType)
struct FEndSkillCameraDitherFadeRelatedActorData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LevelID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    ENDGAME_API FEndSkillCameraDitherFadeRelatedActorData();
};

