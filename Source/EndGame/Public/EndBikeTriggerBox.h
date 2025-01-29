#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EEndBikeTriggerBoxType.h"
#include "EndBikeTriggerBox.generated.h"

class AActor;

UCLASS(Abstract, Blueprintable)
class AEndBikeTriggerBox : public ATriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeTriggerBoxType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> Keys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetIds;
    
    AEndBikeTriggerBox(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
    
    UFUNCTION(BlueprintCallable)
    void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
    
};

