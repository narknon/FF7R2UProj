#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndNaviMapDataProviderInterface.h"
#include "End2FieldActionActorBase.generated.h"

class UEndAnimSet;
class UObject;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEnd2FieldActionActorBase : public AActor, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UEndAnimSet*> AnimSets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNpcEndMotionIsForceFastMove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableDeactiveByHidden;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> FieldAdditionalAssetUserData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 FieldActionActorHashVersion;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 FieldActionActorHash32;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint64 FieldActionActorHash64;
    
public:
    AEnd2FieldActionActorBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void TestTargetIconAction();
    

    // Fix for true pure virtual functions not being implemented
};

