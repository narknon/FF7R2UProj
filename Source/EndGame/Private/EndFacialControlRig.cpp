#include "EndFacialControlRig.h"

UEndFacialControlRig::UEndFacialControlRig() {
    this->EyeBoneNames.AddDefaulted(2);
    this->EyelidsBoneNames.AddDefaulted(28);
    this->ForeheadBoneNames.AddDefaulted(3);
    this->GlabellaBoneNames.AddDefaulted(3);
    this->BrowBoneNames.AddDefaulted(6);
    this->EyeMoveBlendSpaceName = TEXT("F_Eyelid_move01");
    this->EyeMoveBlendInterpSpeed = 20.00f;
    this->LookAtWeightBias = 0.80f;
    this->LookAtUpWeightBias = 0.90f;
    this->SaccadeMoveAngleMax = 7.00f;
    this->SaccadeMoveAngleSoftLimitRate = 0.05f;
    this->FixationVelocityThreshold = 400.00f;
    this->MicroSaccadeMoveAngle = 0.60f;
    this->RandomAdditiveSaccadeMoveAngle = 7.00f;
    this->RandomAdditiveSaccadeTimeDuration = 0.80f;
    this->BlinkPoseName = TEXT("F_Eyelid_blink01");
    this->BlinkThreshold = 0.10f;
    this->FullBlinkThreshold = 0.80f;
    this->PeriodicBlinkCurve = NULL;
    this->ReflectiveBlinkCurve = NULL;
    this->RefrectiveBlinkSaccadeMoveAngleThreshold = 30.00f;
    this->RefrectiveBlinkIntervalMin = 0.50f;
    this->LipSyncBrowMoveBlendSpaceName = TEXT("F_Clm");
    this->DefaultEmotionBlendInputInterpSpeed = 5.00f;
    this->EmotionBlendCurve = NULL;
    this->EmotionTimeOffset = 0.00f;
    this->EmotionLerpMaxLevel = 0;
}


