#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_ParameterType.generated.h"

UENUM(BlueprintType)
enum ESQEX_KD_ParameterType {
    ESQEX_KD_ParameterType_Other,
    ESQEX_KD_ParameterType_TranslateX,
    ESQEX_KD_ParameterType_TranslateY,
    ESQEX_KD_ParameterType_TranslateZ,
    ESQEX_KD_ParameterType_Distance,
    ESQEX_KD_ParameterType_RotateQuatX_DEPLECATED,
    ESQEX_KD_ParameterType_RotateQuatY_DEPLECATED,
    ESQEX_KD_ParameterType_RotateQuatZ_DEPLECATED,
    ESQEX_KD_ParameterType_RotateQuatW_DEPLECATED,
    ESQEX_KD_ParameterType_RotateAngle,
    ESQEX_KD_ParameterType_BendingQuatX_DEPLECATED,
    ESQEX_KD_ParameterType_BendingQuatY_DEPLECATED,
    ESQEX_KD_ParameterType_BendingQuatZ_DEPLECATED,
    ESQEX_KD_ParameterType_BendingQuatW_DEPLECATED,
    ESQEX_KD_ParameterType_BendingAngle,
    ESQEX_KD_ParameterType_BendS,
    ESQEX_KD_ParameterType_BendT,
    ESQEX_KD_ParameterType_Roll,
    ESQEX_KD_ParameterType_QuatAngle,
    ESQEX_KD_ParameterType_ScaleX,
    ESQEX_KD_ParameterType_ScaleY,
    ESQEX_KD_ParameterType_ScaleZ,
    ESQEX_KD_ParameterType_Input,
    ESQEX_KD_ParameterType_Output,
    ESQEX_KD_ParameterType_Translate,
    ESQEX_KD_ParameterType_RollBend,
    ESQEX_KD_ParameterType_RotateQuat,
    ESQEX_KD_ParameterType_BendingQuat,
    ESQEX_KD_ParameterType_Expmap,
    ESQEX_KD_ParameterType_ExpmapX,
    ESQEX_KD_ParameterType_ExpmapY,
    ESQEX_KD_ParameterType_ExpmapZ,
    ESQEX_KD_ParameterType_Scale,
};

