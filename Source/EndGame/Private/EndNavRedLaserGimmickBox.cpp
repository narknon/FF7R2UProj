#include "EndNavRedLaserGimmickBox.h"
#include "ECollisionAndNavProfileType.h"

AEndNavRedLaserGimmickBox::AEndNavRedLaserGimmickBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CollisionAndNavProfileType = ECollisionAndNavProfileType::NoCollision;
}


