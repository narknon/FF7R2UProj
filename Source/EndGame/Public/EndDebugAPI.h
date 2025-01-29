#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndDebugAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndDebugAPI : public UObject {
    GENERATED_BODY()
public:
    UEndDebugAPI();

    UFUNCTION(BlueprintCallable)
    static TArray<FString> UpdateSelectHistory(const TArray<FString>& List, bool changeOrder);
    
    UFUNCTION(BlueprintCallable)
    static void TraceGPU();
    
    UFUNCTION(BlueprintCallable)
    static void StopCPUCapture();
    
    UFUNCTION(BlueprintCallable)
    static void StartCPUCapture();
    
    UFUNCTION(BlueprintCallable)
    static void SetControlRotation(float Pitch, float Yaw, float Roll);
    
    UFUNCTION(BlueprintCallable)
    static void RequestExit();
    
    UFUNCTION(BlueprintCallable)
    static void PrintMemory();
    
    UFUNCTION(BlueprintCallable)
    static bool IsCompletedTrace();
    
    UFUNCTION(BlueprintCallable)
    static FString GetPVActionID(FName PVID);
    
    UFUNCTION(BlueprintCallable)
    static bool GetDebugStateBool(FName TableID, bool defaultBool);
    
    UFUNCTION(BlueprintCallable)
    static FString GetDebugState(FName TableID, const FString& defaultState);
    
    UFUNCTION(BlueprintCallable)
    static FString GetCutSceneEventID(FName Action);
    
    UFUNCTION(BlueprintCallable)
    static FString GetCutSceneActionID(FName CutSceneID);
    
    UFUNCTION(BlueprintCallable)
    static void AddSelectHistory(const FString& str);
    
    UFUNCTION(BlueprintCallable)
    static void AddAction(FName Action);
    
};

