#pragma once
#include "CoreMinimal.h"
#include "EEndStreamingSwitchType.h"
#include "EndStreamingSwitchSet.h"
#include "EndStreamingVolume.h"
#include "EndStreamingSwitchVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndStreamingSwitchVolume : public AEndStreamingVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndStreamingSwitchType SwitchType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AreaSwitchLabel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NoneSwitchLabel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndStreamingSwitchSet> SwitchLevelSets;
    
    AEndStreamingSwitchVolume(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SwitchStreamingVolume(FName InSwitchLabel, EEndStreamingSwitchType InSwitchType, bool NoErrMsg);
    
};

