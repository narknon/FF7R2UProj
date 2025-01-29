#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SQEXSEADLayoutSound.generated.h"

class USQEXSEADLayoutComponent;

UCLASS(Blueprintable, MinimalAPI)
class ASQEXSEADLayoutSound : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USQEXSEADLayoutComponent* LayoutComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bSyncActorHidden: 1;
    
    ASQEXSEADLayoutSound(const FObjectInitializer& ObjectInitializer);

};

