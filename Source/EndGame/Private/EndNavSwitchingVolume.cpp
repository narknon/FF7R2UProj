#include "EndNavSwitchingVolume.h"
#include "EndNavAreaVersatile.h"
#include "EndNavModifierComponent.h"

AEndNavSwitchingVolume::AEndNavSwitchingVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaVersatile::StaticClass();
    this->NavModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("NavModifier"));
    this->bRefreshNav = true;
    this->bNavCreateObbCheck = true;
    this->bUpdateNavArea = true;
    this->CollisionProfileType = ECollisionProfileType::Wall;
    this->CollisionAndNavProfileType = ECollisionAndNavProfileType::Wall;
    this->bActiveInBattle = false;
    this->bPC_Wall = true;
    this->bParty_Wall = true;
    this->bSubParty_Wall = true;
    this->bNPC_Wall = true;
    this->bEnemy_Wall = true;
    this->bEnablePhysicsBodyBlock = false;
    this->ExtraOption = ECollisionProfileExtraOption::Default;
    this->CameraResponse = ECR_Ignore;
}


