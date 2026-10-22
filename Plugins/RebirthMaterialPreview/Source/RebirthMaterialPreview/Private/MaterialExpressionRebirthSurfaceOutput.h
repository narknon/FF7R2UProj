#pragma once

#include "CoreMinimal.h"
#include "MaterialExpressionIO.h"
#include "Materials/MaterialExpressionCustomOutput.h"
#include "MaterialExpressionRebirthSurfaceOutput.generated.h"

/** Explicit original-surface inputs for the recovered skin/fabric bridge. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API UMaterialExpressionRebirthSurfaceOutput : public UMaterialExpressionCustomOutput
{
    GENERATED_UCLASS_BODY()

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput NormalWS;

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput Roughness;

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput MaterialAO;

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput SurfaceDiffusion;

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput Sentinel;

#if WITH_EDITOR
    virtual int32 Compile(FMaterialCompiler* Compiler, int32 OutputIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual uint32 GetInputType(int32 InputIndex) override { return InputIndex == 0 ? MCT_Float3 : MCT_Float1; }
    virtual FExpressionInput* GetInput(int32 InputIndex) override;
#endif
    virtual int32 GetNumOutputs() const override { return 5; }
    virtual FString GetFunctionName() const override { return TEXT("RebirthSurfaceBridge"); }
    virtual FString GetDisplayName() const override { return TEXT("Rebirth Surface Data"); }
};
