#pragma once
#include "CoreMinimal.h"
#include "NavPriorRegistInfo.h"
#include "EndFieldActionNavLinkActorBase.h"
#include "EndNavActorInterface.h"
#include "EndFieldActionNavLinkActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionNavLinkActor : public AEndFieldActionNavLinkActorBase, public IEndNavActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRefreshNavLink;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndFieldActionNavLinkActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

