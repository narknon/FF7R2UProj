#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndActionYuffieBox.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndActionYuffieBox : public AEndEnvironmentPhysicsStaticMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector FailLocation;
    
    AEndActionYuffieBox(const FObjectInitializer& ObjectInitializer);

};

