#include "EndAerialModule.h"

FEndAerialModule::FEndAerialModule() {
    this->X_POINT_MAX = 0;
    this->Y_POINT_MAX = 0;
    this->Z_POINT_MAX = 0;
    this->EnableEqualInterval = false;
    this->CanEverAffectNavigation = false;
    this->IsAffectedTerritory = false;
    this->NotCheckCollision = false;
    this->NotCheckGameCameraCollision = false;
    this->bCreateUnderFloorPoint = false;
    this->bAllowIsoLated = false;
    this->bAllowInWater = false;
    this->bForceCreatePoint = false;
    this->X_CM_SPACE_MAX = 0;
    this->Y_CM_SPACE_MAX = 0;
    this->Z_CM_SPACE_MAX = 0;
    this->XPointNum = 0;
    this->YPointNum = 0;
    this->ZPointNum = 0;
    this->PointMaxNum = 0;
}

