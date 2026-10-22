#pragma once

#include "CoreMinimal.h"
#include "MaterialExpressionIO.h"
#include "Materials/MaterialExpressionCustomOutput.h"
#include "MaterialExpressionRebirthHairOutput.generated.h"

/** Explicit opt-in for the recovered Rebirth hair surface/lighting adapter. */
UCLASS()
class REBIRTHMATERIALPREVIEW_API UMaterialExpressionRebirthHairOutput : public UMaterialExpressionCustomOutput
{
    GENERATED_UCLASS_BODY()

    UPROPERTY(meta = (RequiredInput = "true"))
    FExpressionInput EncodedWideBentNormal;

#if WITH_EDITOR
    virtual int32 Compile(FMaterialCompiler* Compiler, int32 OutputIndex) override;
    virtual void GetCaption(TArray<FString>& OutCaptions) const override;
    virtual uint32 GetInputType(int32 InputIndex) override { return MCT_Float3; }
    virtual FExpressionInput* GetInput(int32 InputIndex) override;
#endif
    virtual int32 GetNumOutputs() const override { return 1; }
    virtual FString GetFunctionName() const override { return TEXT("RebirthHairBridge"); }
    virtual FString GetDisplayName() const override { return TEXT("Rebirth Hair Data"); }
};
