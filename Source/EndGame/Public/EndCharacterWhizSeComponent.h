#pragma once
#include "CoreMinimal.h"
#include "SQEXSEADWhizSeComponent.h"
#include "EndCharacterWhizSeComponent.generated.h"

class USoundBase;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndCharacterWhizSeComponent : public USQEXSEADWhizSeComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<USoundBase> SoundRef;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SoundName;
    
    UEndCharacterWhizSeComponent(const FObjectInitializer& ObjectInitializer);

};

