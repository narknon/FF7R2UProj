#pragma once
#include "CoreMinimal.h"
#include "EndNavLinkProxy.h"
#include "EndNavWorldGeneralJumpActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNavWorldGeneralJumpActor : public AEndNavLinkProxy {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNextBuildSave;
    
    AEndNavWorldGeneralJumpActor(const FObjectInitializer& ObjectInitializer);

};

