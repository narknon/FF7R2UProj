#pragma once
#include "CoreMinimal.h"
#include "EndAIActionDefinitionBase.h"
#include "EndAIActionPackTransInfo.h"
#include "EndAITransDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAITransDefinition : public UEndAIActionDefinitionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIActionPackTransInfo TransInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActionDefTag;
    
    UEndAITransDefinition();

};

