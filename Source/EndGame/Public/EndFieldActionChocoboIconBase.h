#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionChocoboMarkerType.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionChocoboIconBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionChocoboIconBase : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFieldActionChocoboMarkerType MarkerTypeEnter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndFieldActionChocoboMarkerType MarkerTypeExit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpawnChocoboDistanceFromIcon;
    
public:
    AEndFieldActionChocoboIconBase(const FObjectInitializer& ObjectInitializer);

};

