#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpressionCustomOutput.h"
#include "MaterialExpressionRebirthEyeOutput.generated.h"

/** Explicit opt-in surface payload for the recovered Rebirth Eye shader path. */
UCLASS(collapsecategories, hidecategories=Object)
class REBIRTHMATERIALPREVIEW_API UMaterialExpressionRebirthEyeOutput : public UMaterialExpressionCustomOutput
{
    GENERATED_UCLASS_BODY()

    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput ScleraNormalWS;
    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput RadialDirectionWS;
    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput IrisNormalPacked;
    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput ScleraMask;
    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput IrisOcclusion;
    UPROPERTY(meta=(RequiredInput="true")) FExpressionInput RadialDistance;

    virtual int32 GetNumOutputs() const override { return 6; }
    virtual FString GetFunctionName() const override { return TEXT("RebirthEyeBridge"); }
    virtual FString GetDisplayName() const override { return TEXT("Recovered Rebirth Eye Surface"); }

#if WITH_EDITOR
    virtual int32 Compile(FMaterialCompiler* Compiler, int32 OutputIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual const TArray<FExpressionInput*> GetInputs() override;
    virtual FExpressionInput* GetInput(int32 InputIndex) override;
    virtual FName GetInputName(int32 InputIndex) const override;
    virtual uint32 GetInputType(int32 InputIndex) override;
#endif
};
