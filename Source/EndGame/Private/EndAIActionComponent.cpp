#include "EndAIActionComponent.h"

UEndAIActionComponent::UEndAIActionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_MoveDefinition = NULL;
    this->m_MoveDefinitionStep = NULL;
    this->m_MoveDefinitionSequence = NULL;
    this->m_OverrideMoveDefinition = NULL;
    this->m_ActionDefinition = NULL;
    this->m_ComboDefinition = NULL;
    this->m_ComboDefinitionConnect = NULL;
    this->m_CombinationDefinition = NULL;
    this->m_ActionPack = NULL;
    this->m_ActionDefinition_InterruptBackup = NULL;
    this->m_ComboDefinition_InterruptBackup = NULL;
    this->m_FieldDefinition = NULL;
}


