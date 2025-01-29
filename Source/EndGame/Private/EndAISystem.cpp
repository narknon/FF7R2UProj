#include "EndAISystem.h"

UEndAISystem::UEndAISystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ControllerManager = NULL;
    this->AutoMagicInfo = NULL;
    this->AIMoveCorrectEdgeMergin = 100.00f;
    this->AIMoveCorrectEdgeMaxRatio = 0.35f;
    this->AIMoveCorneringDistance = 350.00f;
    this->AIMoveRouteInterpSlopeRatio = 0.80f;
    this->AsyncNavProcessingAllowableTime = 0.00f;
    this->AsyncNavProcessingAllowableTimeLong = 0.00f;
    this->AIStatesInterestedByAnimals.AddDefaulted(2);
}

void UEndAISystem::LoadBehaviorTreeAsset(UBehaviorTree* Asset) {
}

void UEndAISystem::ClearEQSAssetCache(UEnvQuery* Asset) {
}

void UEndAISystem::ClearBehaviorTreeAssetCache(UBehaviorTree* Asset) {
}


