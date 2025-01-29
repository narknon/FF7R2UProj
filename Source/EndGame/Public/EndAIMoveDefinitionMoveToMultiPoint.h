#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionMoveToMultiPointBase.h"
#include "EndAIMoveDefinitionMoveToMultiPoint.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionMoveToMultiPoint : public UEndAIMoveDefinitionMoveToMultiPointBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseReservePoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableBattleInvisibleWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPathFind;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideCharacterHeight;
    
    UEndAIMoveDefinitionMoveToMultiPoint();

};

