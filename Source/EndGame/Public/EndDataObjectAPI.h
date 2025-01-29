#pragma once
#include "CoreMinimal.h"
#include "EndDataBaseDataObjectAPI.h"
#include "EDataObjectType.h"
#include "EndDataObjectAPI.generated.h"

class AEndAssetActor;

UCLASS(Blueprintable)
class ENDGAME_API UEndDataObjectAPI : public UEndDataBaseDataObjectAPI {
    GENERATED_BODY()
public:
    UEndDataObjectAPI();

    UFUNCTION(BlueprintCallable)
    static void UnInitDataObject(EDataObjectType Type, FName LocationId, AEndAssetActor* Asset);
    
    UFUNCTION(BlueprintCallable)
    static void InitDataObject(EDataObjectType Type, FName LocationId, AEndAssetActor* Asset);
    
    UFUNCTION(BlueprintCallable)
    static void DebugReimportDataObject(const FString& residentOrLocation);
    
    UFUNCTION(BlueprintCallable)
    static void Debug_UninitAllLocation();
    
    UFUNCTION(BlueprintCallable)
    static void Debug_InitAllLocation();
    
};

