#include "EndMobRouteSplineNonLoop.h"
#include "EndMobRouteSplineComponent.h"

AEndMobRouteSplineNonLoop::AEndMobRouteSplineNonLoop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndMobRouteSplineComponent>(TEXT("SplineMoveComponent"))) {
    this->bBindToMobPrefab_Head = false;
    this->MobPrefabClass_Head = NULL;
    this->bStopBeforeBind_Head = false;
    this->bLookAt_Head = false;
    this->bSetLocationWork_Head = false;
    this->LocationWorkValue_Head = 0;
    this->bBindToMobPrefab_Tail = false;
    this->MobPrefabClass_Tail = NULL;
    this->bStopBeforeBind_Tail = false;
    this->bLookAt_Tail = false;
    this->bSetLocationWork_Tail = false;
    this->LocationWorkValue_Tail = 0;
    this->SplineMoveComponent->SetupAttachment(RootComponent);
}


