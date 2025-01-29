#pragma once
#include "CoreMinimal.h"
#include "EndDeformAnimationComponentBase.h"
#include "EndDeformAnimationSettings.h"
#include "EndDeformAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDeformAnimationComponent : public UEndDeformAnimationComponentBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndDeformAnimationSettings DeformAnimationSettings;
    
    UEndDeformAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

