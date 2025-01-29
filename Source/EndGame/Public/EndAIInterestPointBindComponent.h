#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InterestPointRequestInfo.h"
#include "EndAIInterestPointBindComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndAIInterestPointBindComponent : public UActorComponent {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FInterestPointRequestInfo> BindInfoList;
    
public:
    UEndAIInterestPointBindComponent(const FObjectInitializer& ObjectInitializer);

};

