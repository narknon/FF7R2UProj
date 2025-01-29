#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "AI/Navigation/NavLinkDefinition.h"
#include "AI/Navigation/NavLinkDefinition.h"
#include "NavLinkHostInterface.h"
#include "End2FieldActionActorBase.h"
#include "EndSmartLinkReachedSignatureDelegate.h"
#include "EndFieldActionNavLinkActorBase.generated.h"

class AActor;
class UNavLinkCustomComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionNavLinkActorBase : public AEnd2FieldActionActorBase, public INavLinkHostInterface, public INavRelevantInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FNavigationLink> PointLinks;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector PointLinkLeftOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector PointLinkRightOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FNavigationSegmentLink> SegmentLinks;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UNavLinkCustomComponent* SmartLinkComp;
    
protected:
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSmartLinkReachedSignature OnSmartLinkReached;
    
public:
    AEndFieldActionNavLinkActorBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetSmartLinkEnabled(bool bEnabled);
    
    UFUNCTION(BlueprintCallable)
    void ResumePathFollowing(AActor* Agent);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ReceiveSmartLinkReached(AActor* Agent, const FVector& Destination);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsSmartLinkEnabled() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasMovingAgents() const;
    

    // Fix for true pure virtual functions not being implemented
};

