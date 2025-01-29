#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndAIMoveDefinitionMoveToMultiPointBase.h"
#include "EndAIMoveDefinitionMoveToMultiBGFA.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionMoveToMultiBGFA : public UEndAIMoveDefinitionMoveToMultiPointBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LevelName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AccessorIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableHit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> IgnoreSelectStateID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D OverrideCapsuleSize;
    
    UEndAIMoveDefinitionMoveToMultiBGFA();

};

