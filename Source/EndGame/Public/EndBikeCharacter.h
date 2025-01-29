#pragma once
#include "CoreMinimal.h"
#include "EndCharacterBase.h"
#include "EndVehicleSeSetting.h"
#include "EndBikeCharacter.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBikeCharacter : public AEndCharacterBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSeSetting SeSetting;
    
    AEndBikeCharacter(const FObjectInitializer& ObjectInitializer);

};

