#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionSaveActorBase.h"
#include "EndFieldOutOfSafeAreaInterface.h"
#include "EndFieldActionMineCartRailActor.generated.h"

class UEndFieldActionTriggerComponent;
class UEndFieldMineCartRailComponent;
class UEndFieldMineCartTargetComponent;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionMineCartRailActor : public AEndFieldActionSaveActorBase, public IEndFieldOutOfSafeAreaInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldMineCartRailComponent*> RailArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndFieldMineCartTargetComponent*> MineCartArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* MineCartVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FinishToFallRailName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FinishToFallStartEventTrigger;
    
public:
    AEndFieldActionMineCartRailActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

