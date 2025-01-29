#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndNavWorldLinkAttrIgnoreVolume.generated.h"

class UEndNavWorldLinkAttrIgnoreBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndNavWorldLinkAttrIgnoreVolume : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavWorldLinkAttrIgnoreBoxComponent* EndAttrIgnoreBoxComponent;
    
    AEndNavWorldLinkAttrIgnoreVolume(const FObjectInitializer& ObjectInitializer);

};

