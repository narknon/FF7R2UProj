#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionAround.h"
#include "EndAIMoveDefinitionAroundSpecialStandby.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionAroundSpecialStandby : public UEndAIMoveDefinitionAround {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupIndividualTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TopPriorityActionIDs;
    
    UEndAIMoveDefinitionAroundSpecialStandby();

};

