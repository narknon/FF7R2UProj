#pragma once
#include "CoreMinimal.h"
#include "EndEmissiveColorComponentBase.h"
#include "EndEmissiveColorComponent.generated.h"

class UEndEmissiveColorSettings;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndEmissiveColorComponent : public UEndEmissiveColorComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndEmissiveColorSettings* EmissiveColorSettings;
    
    UEndEmissiveColorComponent(const FObjectInitializer& ObjectInitializer);

};

