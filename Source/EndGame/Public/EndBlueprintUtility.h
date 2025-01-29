#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EEndAIBranch2.h"
#include "EEndAIBranch2Other.h"
#include "EEndAIBranch3.h"
#include "EEndAIBranch3Other.h"
#include "EEndAIBranch4.h"
#include "EEndAIBranch4Other.h"
#include "EEndAIBranch5.h"
#include "EEndAIBranch6.h"
#include "EEndAIBranch7.h"
#include "EEndAIBranch8.h"
#include "EEndAIBranchBit.h"
#include "EEndAiMathCmp.h"
#include "EndBlueprintUtility.generated.h"

class AActor;

UCLASS(Blueprintable)
class UEndBlueprintUtility : public UObject {
    GENERATED_BODY()
public:
    UEndBlueprintUtility();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float VecToYaw(const FVector& InVec);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float VecToPitch(const FVector& InVec);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch8(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, int32 Case7, int32 Case8, TEnumAsByte<EEndAIBranch8::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch7(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, int32 Case7, TEnumAsByte<EEndAIBranch7::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch6(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, int32 Case6, TEnumAsByte<EEndAIBranch6::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch5(int32 Case1, int32 Case2, int32 Case3, int32 Case4, int32 Case5, TEnumAsByte<EEndAIBranch5::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch4(int32 Case1, int32 Case2, int32 Case3, int32 Case4, TEnumAsByte<EEndAIBranch4::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch3(int32 Case1, int32 Case2, int32 Case3, TEnumAsByte<EEndAIBranch3::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RatioBranch2(int32 Case1, int32 Case2, TEnumAsByte<EEndAIBranch2::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RangeSwitch4(float Value, float Min1, float Max1, float Min2, float Max2, float Min3, float Max3, float Min4, float Max4, bool bContainEqual, TEnumAsByte<EEndAIBranch4Other::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RangeSwitch3(float Value, float Min1, float Max1, float Min2, float Max2, float Min3, float Max3, bool bContainEqual, TEnumAsByte<EEndAIBranch3Other::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void RangeSwitch2(float Value, float Min1, float Max1, float Min2, float Max2, bool bContainEqual, TEnumAsByte<EEndAIBranch2Other::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static int32 PlusEqualInterger(UPARAM(Ref) int32& ValueA, int32 ValueB);
    
    UFUNCTION(BlueprintCallable)
    static float PlusEqualFloat(UPARAM(Ref) float& ValueA, float ValueB);
    
    UFUNCTION(BlueprintCallable)
    static int32 MulEqualInterger(UPARAM(Ref) int32& ValueA, int32 ValueB);
    
    UFUNCTION(BlueprintCallable)
    static float MulEqualFloat(UPARAM(Ref) float& ValueA, float ValueB);
    
    UFUNCTION(BlueprintCallable)
    static int32 MinusEqualInterger(UPARAM(Ref) int32& ValueA, int32 ValueB);
    
    UFUNCTION(BlueprintCallable)
    static float MinusEqualFloat(UPARAM(Ref) float& ValueA, float ValueB);
    
    UFUNCTION(BlueprintCallable)
    static void IntCmpBranch(int32 ValueA, int32 ValueB, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetVectorRange(float X, float Y, float Z, float IgnoreX, float IgnoreY, float IgnoreZ);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetRatioSwitch3(int32 Switch0, int32 Switch1, int32 Switch2);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetRatioSwitch2(int32 Switch0, int32 Switch1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetRatioSwitch(TArray<int32> inArray);
    
    UFUNCTION(BlueprintCallable)
    static void FloatCmpBranch(float ValueA, float ValueB, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void EnableInputDebug(AActor* Target);
    
    UFUNCTION(BlueprintCallable)
    static int32 DivEqualInterger(UPARAM(Ref) int32& ValueA, int32 ValueB);
    
    UFUNCTION(BlueprintCallable)
    static float DivEqualFloat(UPARAM(Ref) float& ValueA, float ValueB);
    
    UFUNCTION(BlueprintCallable)
    static void DisableInputDebug(AActor* Target);
    
    UFUNCTION(BlueprintCallable)
    static void BranchXOR(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void BranchOR(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable)
    static void BranchAnd(bool Flag1, bool Flag2, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
};

