#include "EndCinemaAttachSection.h"

UEndCinemaAttachSection::UEndCinemaAttachSection() {
    this->AttachmentLocationRule = EAttachmentRule::SnapToTarget;
    this->AttachmentRotationRule = EAttachmentRule::SnapToTarget;
    this->AttachmentScaleRule = EAttachmentRule::SnapToTarget;
    this->DetachmentLocationRule = EDetachmentRule::KeepWorld;
    this->DetachmentRotationRule = EDetachmentRule::KeepWorld;
    this->DetachmentScaleRule = EDetachmentRule::KeepWorld;
}


