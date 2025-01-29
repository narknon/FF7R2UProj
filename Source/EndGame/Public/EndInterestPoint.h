#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndInterestPointReactionActorType.h"
#include "EEndInterestPointTemplate.h"
#include "EndInteractorInterface.h"
#include "EndInterestPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndInterestPoint : public AActor, public IEndInteractorInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndInterestPointReactionActorType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InterestRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndInterestPointTemplate InterestTemplateID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName InterestOverrideID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsForcedRecognition;
    
public:
    AEndInterestPoint(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

