#include "EndEnvironmentStaticMeshActor.h"
#include "EndEnvironmentStaticMeshComponent.h"
#include "EndNavAreaVersatile.h"

AEndEnvironmentStaticMeshActor::AEndEnvironmentStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndEnvironmentStaticMeshComponent>(TEXT("StaticMeshComponent0"))) {
    this->bCanBeInCluster = true;
    const FProperty* p_StaticMeshComponent = GetClass()->FindPropertyByName("StaticMeshComponent");
    (*p_StaticMeshComponent->ContainerPtrToValuePtr<UStaticMeshComponent*>(this)) = (UStaticMeshComponent*)RootComponent;
    this->bAlwaysHiddenActor = false;
    this->bCanSkillCameraDitherFade = false;
    this->bDrawPauseNavigation = false;
    this->AreaClass = UEndNavAreaVersatile::StaticClass();
    this->OverwriteNearFadeDistance = -1.00f;
    this->OverwriteNearFadeDistanceOnBattle = -1.00f;
}


