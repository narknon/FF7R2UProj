#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EMoogleAITrickType.h"
#include "EndAIController.h"
#include "EndMoogleCaptureAIController.generated.h"

class AEndCharacter;
class UEnvQuery;

UCLASS(Blueprintable)
class ENDGAME_API AEndMoogleCaptureAIController : public AEndAIController {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseDefaultBarrage;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* WonderingEQS;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceRemove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 LimitBulletNum;
    
public:
    AEndMoogleCaptureAIController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    bool ThrowSpawnedTrick(FVector launchOffset, FVector initvel, int32 usingidx);
    
    UFUNCTION(BlueprintCallable)
    bool ShootBullet(FVector launchPos, FVector aimLoc);
    
    UFUNCTION(BlueprintCallable)
    void SetAccel(FVector Accel);
    
    UFUNCTION(BlueprintCallable)
    void PlayTrickBarrageAnim(FName AnimName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnThrowTrick();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartBarrage();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFinishBarrage();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsBarrage() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsArrested() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetTrickParameter() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetStageClearCount();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetOwnerMoogle();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCurrentStage();
    
    UFUNCTION(BlueprintCallable)
    bool FireBullet(FVector launchPos, FVector initvel);
    
    UFUNCTION(BlueprintCallable)
    void BranchTrickType(EMoogleAITrickType& OutTrickType);
    
};

