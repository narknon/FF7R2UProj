#include "SQEXSEADAnimNotifyState_ChangeAutoSeEnable.h"

USQEXSEADAnimNotifyState_ChangeAutoSeEnable::USQEXSEADAnimNotifyState_ChangeAutoSeEnable() {
    this->bEnableAutoSeEnableParameters = true;
    this->bEnableSetting = false;
    this->NotifyEndBehavior = ESQEXSEADChangeAutoSeEnableNotifyEndBehavior::RevertState;
    this->bEnableContinuousDisabling = false;
    this->bEnableMotionDetectFilters = false;
    this->bMotionDetectFilterAsGlobal = false;
}


