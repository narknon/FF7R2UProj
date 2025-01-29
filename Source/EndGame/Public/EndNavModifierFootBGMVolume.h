#pragma once
#include "CoreMinimal.h"
#include "EndNavModifierVolumeBase.h"
#include "EndNavModifierFootBGMVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavModifierFootBGMVolume : public AEndNavModifierVolumeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _footBGMSetID;
    
    AEndNavModifierFootBGMVolume(const FObjectInitializer& ObjectInitializer);

};

