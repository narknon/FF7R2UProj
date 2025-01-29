#include "EndBlueprintUtility.h"

UEndBlueprintUtility::UEndBlueprintUtility() {
}

float UEndBlueprintUtility::VecToYaw(const FVector& InVec) {
    return 0.0f;
}

float UEndBlueprintUtility::VecToPitch(const FVector& InVec) {
    return 0.0f;
}

void UEndBlueprintUtility::RatioBranch8(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, int32 Case7, int32 Case8, TEnumAsByte<EEndAIBranch8::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch7(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, int32 Case7, TEnumAsByte<EEndAIBranch7::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch6(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, TEnumAsByte<EEndAIBranch6::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch5(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, TEnumAsByte<EEndAIBranch5::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch4(int32 Case1, int32 Case2, int32 Case3, int32 Case4, TEnumAsByte<EEndAIBranch4::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch3(int32 Case1, int32 Case2, int32 Case3, TEnumAsByte<EEndAIBranch3::Type>& OutSignal) {
}

void UEndBlueprintUtility::RatioBranch2(int32 Case1, int32 Case2, TEnumAsByte<EEndAIBranch2::Type>& OutSignal) {
}

void UEndBlueprintUtility::RangeSwitch4(float Value, float Min1, float Max1, float Min2, float Max2, float Min3, float Max3, float Min4, float Max4, bool bContainEqual, TEnumAsByte<EEndAIBranch4Other::Type>& OutSignal) {
}

void UEndBlueprintUtility::RangeSwitch3(float Value, float Min1, float Max1, float Min2, float Max2, float Min3, float Max3, bool bContainEqual, TEnumAsByte<EEndAIBranch3Other::Type>& OutSignal) {
}

void UEndBlueprintUtility::RangeSwitch2(float Value, float Min1, float Max1, float Min2, float Max2, bool bContainEqual, TEnumAsByte<EEndAIBranch2Other::Type>& OutSignal) {
}

int32 UEndBlueprintUtility::PlusEqualInterger(int32& ValueA, int32 ValueB) {
    return 0;
}

float UEndBlueprintUtility::PlusEqualFloat(float& ValueA, float ValueB) {
    return 0.0f;
}

int32 UEndBlueprintUtility::MulEqualInterger(int32& ValueA, int32 ValueB) {
    return 0;
}

float UEndBlueprintUtility::MulEqualFloat(float& ValueA, float ValueB) {
    return 0.0f;
}

int32 UEndBlueprintUtility::MinusEqualInterger(int32& ValueA, int32 ValueB) {
    return 0;
}

float UEndBlueprintUtility::MinusEqualFloat(float& ValueA, float ValueB) {
    return 0.0f;
}

void UEndBlueprintUtility::IntCmpBranch(int32 ValueA, int32 ValueB, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}

FVector UEndBlueprintUtility::GetVectorRange(float X, float Y, float Z, float IgnoreX, float IgnoreY, float IgnoreZ) {
    return FVector{};
}

int32 UEndBlueprintUtility::GetRatioSwitch3(int32 Switch0, int32 Switch1, int32 Switch2) {
    return 0;
}

int32 UEndBlueprintUtility::GetRatioSwitch2(int32 Switch0, int32 Switch1) {
    return 0;
}

int32 UEndBlueprintUtility::GetRatioSwitch(TArray<int32> inArray) {
    return 0;
}

void UEndBlueprintUtility::FloatCmpBranch(float ValueA, float ValueB, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}

void UEndBlueprintUtility::EnableInputDebug(AActor* Target) {
}

int32 UEndBlueprintUtility::DivEqualInterger(int32& ValueA, int32 ValueB) {
    return 0;
}

float UEndBlueprintUtility::DivEqualFloat(float& ValueA, float ValueB) {
    return 0.0f;
}

void UEndBlueprintUtility::DisableInputDebug(AActor* Target) {
}

void UEndBlueprintUtility::BranchXOR(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}

void UEndBlueprintUtility::BranchOR(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}

void UEndBlueprintUtility::BranchAnd(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}


