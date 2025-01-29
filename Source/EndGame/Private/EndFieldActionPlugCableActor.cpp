#include "EndFieldActionPlugCableActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionPlugCableActor::AEndFieldActionPlugCableActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->RopeLength = 1000.00f;
    this->CanSetPlugRopeMaxLength = 1000.00f;
    this->RopeSourceToPlugLimitDistance = -1.00f;
    this->BreakAttachPlugRopeLength = -1.00f;
    this->bRopeCatchOnlyEnd = false;
    this->bNoLimitMode = false;
    this->MineCartActor = NULL;
    this->bCanReverseRopeSetting = false;
    this->RopeObjectClass = NULL;
    this->RopeObjectClassForAirpurifierCart = NULL;
    this->RopeObjectClassForGongaga = NULL;
    this->CartMoveLimitSpline = NULL;
    this->PlugOffEmissiveIntensityAlpha = 100.00f;
    this->PlugOnEmissiveIntensityAlpha = 100.00f;
    this->SoundBank_PlugLanded = NULL;
    this->UpperVolume->SetupAttachment(RootComponent);
}


