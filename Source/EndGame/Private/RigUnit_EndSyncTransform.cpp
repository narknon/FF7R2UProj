#include "RigUnit_EndSyncTransform.h"

FRigUnit_EndSyncTransform::FRigUnit_EndSyncTransform() {
    this->Space = EBoneGetterSetterMode::LocalSpace;
    this->bInitial = false;
}

