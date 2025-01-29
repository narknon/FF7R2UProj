#pragma once
#include "CoreMinimal.h"
#include "CollisionExtraAttributes.h"
#include "EndStaticMeshComponent.h"
#include "EndEnvironmentStaticMeshComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndEnvironmentStaticMeshComponent : public UEndStaticMeshComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bOverrideCollisionExtraAttribute: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FCollisionExtraAttributes CollisoinExtraAttribute;
    
    UEndEnvironmentStaticMeshComponent(const FObjectInitializer& ObjectInitializer);

};

