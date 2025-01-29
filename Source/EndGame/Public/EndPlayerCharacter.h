#pragma once
#include "CoreMinimal.h"
#include "EndChangeAppearanceCharacter.h"
#include "Templates/SubclassOf.h"
#include "EndPlayerCharacter.generated.h"

class UEndPlayerCharacterConfig;

UCLASS(Blueprintable)
class ENDGAME_API AEndPlayerCharacter : public AEndChangeAppearanceCharacter {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndPlayerCharacterConfig> PlayerConfig;
    
public:
    AEndPlayerCharacter(const FObjectInitializer& ObjectInitializer);

};

