#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndFieldSimpleInteractNameMatchingEditOnly.h"
#include "EndFieldSimpleInteractStateSetting.h"
#include "EndFieldSimpleInteractTransformMatching.h"
#include "EndFieldSimpleInteractStateSettingObject.generated.h"

UCLASS(Abstract, Blueprintable, MinimalAPI, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldSimpleInteractStateSettingObject : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractStateSetting> StateSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MatchingNameNum;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractNameMatchingEditOnly> MatchingNameArrayEdit;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MatchingTransformNum;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FEndFieldSimpleInteractTransformMatching> MachingTransformArrayEdit;
    
    UEndFieldSimpleInteractStateSettingObject(const FObjectInitializer& ObjectInitializer);

};

