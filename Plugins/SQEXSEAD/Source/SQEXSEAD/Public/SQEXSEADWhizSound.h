#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SQEXSEADWhizSound.generated.h"

class USQEXSEADWhizSeComponent;
class USoundBase;

UCLASS(Blueprintable, MinimalAPI)
class ASQEXSEADWhizSound : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* Sound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USQEXSEADWhizSeComponent* WhizComponent;
    
    ASQEXSEADWhizSound(const FObjectInitializer& ObjectInitializer);

};

