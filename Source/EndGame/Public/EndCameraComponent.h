#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "EndCameraComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndCameraComponent : public UCameraComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float FocalLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float FocusDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float FilmWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    float Roll;
    
    UEndCameraComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetRoll(float NewValue);
    
    UFUNCTION(BlueprintCallable)
    void SetHorizontalAperture(float NewValue);
    
    UFUNCTION(BlueprintCallable)
    void SetFocusDistance(float NewValue);
    
    UFUNCTION(BlueprintCallable)
    void SetFocalLength(float NewValue);
    
};

