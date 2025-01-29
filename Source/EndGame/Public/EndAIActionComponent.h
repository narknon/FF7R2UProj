#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndAIActionComponent.generated.h"

class UEndAIActionDefinitionBase;
class UEndAIActionPackBase;
class UEndAICombinationDefinition;
class UEndAIComboDefinition;
class UEndAIComboDefinitionConnect;
class UEndAIFieldDefinitionBase;
class UEndAIMoveDefinition;
class UEndAIMoveDefinitionSequence;
class UEndAIMoveDefinitionStep;
class UEndAITransDefinition;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAIActionComponent : public UActorComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIMoveDefinition* m_MoveDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIMoveDefinitionStep* m_MoveDefinitionStep;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIMoveDefinitionSequence* m_MoveDefinitionSequence;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIMoveDefinition* m_OverrideMoveDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIActionDefinitionBase* m_ActionDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UEndAITransDefinition*> m_TransDefinitions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIComboDefinition* m_ComboDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIComboDefinitionConnect* m_ComboDefinitionConnect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAICombinationDefinition* m_CombinationDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIActionPackBase* m_ActionPack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIActionDefinitionBase* m_ActionDefinition_InterruptBackup;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIComboDefinition* m_ComboDefinition_InterruptBackup;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndAIFieldDefinitionBase* m_FieldDefinition;
    
public:
    UEndAIActionComponent(const FObjectInitializer& ObjectInitializer);

};

