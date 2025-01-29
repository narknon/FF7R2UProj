#include "EndTinyBroncoCharacter.h"

AEndTinyBroncoCharacter::AEndTinyBroncoCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DitherFadeSettingFlag = 1;
    this->bUpdateFootAttributeWithoutAutoSeSetting = true;
    this->MovementSetting = NULL;
}

void AEndTinyBroncoCharacter::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
}


