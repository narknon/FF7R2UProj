#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionChocoboIconBase.h"
#include "EndFieldActionChocoboUpdraftInterface.h"
#include "EndFieldActionChocoboUpdraftParam.h"
#include "EndFieldActionChocoboUpdraftActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionChocoboUpdraftActor : public AEndFieldActionChocoboIconBase, public IEndFieldActionChocoboUpdraftInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldActionChocoboUpdraftParam Param;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector IconOffsetLocation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator IconOffsetRotation;
    
public:
    AEndFieldActionChocoboUpdraftActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

