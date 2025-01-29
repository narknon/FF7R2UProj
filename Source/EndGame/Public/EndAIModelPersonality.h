#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EndAIModelPersonality.generated.h"

UCLASS(Abstract, Blueprintable, CollapseCategories, Const)
class ENDGAME_API UEndAIModelPersonality : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ExperienceSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D ExperienceSpeedRandomBias;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RemoveRecognitionTime;
    
    UEndAIModelPersonality();

};

