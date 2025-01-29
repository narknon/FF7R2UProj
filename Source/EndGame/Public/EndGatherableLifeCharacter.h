#pragma once
#include "CoreMinimal.h"
#include "EndCharacter.h"
#include "EndGatherableLife.h"
#include "EndGatherableLifeCharacter.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndGatherableLifeCharacter : public AEndCharacter {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndGatherableLife m_Worker;
    
    AEndGatherableLifeCharacter(const FObjectInitializer& ObjectInitializer);

};

