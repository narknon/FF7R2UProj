#pragma once
#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "EndCylinderComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndCylinderComponent : public UShapeComponent {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    float CylinderHalfHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    float CylinderRadius;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Export, meta=(AllowPrivateAccess=true))
    int32 CylinderSides;
    
public:
    UEndCylinderComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetCylinderSize(float InRadius, float InHalfHeight, int32 InCylinderSides, bool bUpdateOverlaps);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetUnscaledCylinderRadius() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetUnscaledCylinderHalfHeight() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetScaledCylinderRadius() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetScaledCylinderHalfHeight() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetCylinderSides() const;
    
};

