#pragma once
#include "CoreMinimal.h"
#include "EEndAIComboSelectType.h"
#include "EndAIActionDefinitionBase.h"
#include "EndAIComboInfo.h"
#include "Templates/SubclassOf.h"
#include "EndAIComboDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAIComboDefinition : public UEndAIActionDefinitionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIActionDefinitionBase> FirstActionDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> FirstDeselectConnectCheckCountCancelNumbers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIComboSelectType SelectType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIComboInfo> ComboInfos;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActionDefTag;
    
    UEndAIComboDefinition();

};

