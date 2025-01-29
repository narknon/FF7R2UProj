#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndCrossSaveManager.generated.h"

class UUserWidget;

UCLASS(Blueprintable)
class ENDGAME_API UEndCrossSaveManager : public UObject {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UUserWidget* MessageWidget;
    
public:
    UEndCrossSaveManager();

};

