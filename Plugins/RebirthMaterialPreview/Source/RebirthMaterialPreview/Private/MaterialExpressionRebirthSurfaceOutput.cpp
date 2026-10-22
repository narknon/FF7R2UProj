#include "MaterialExpressionRebirthSurfaceOutput.h"
#include "MaterialCompiler.h"

UMaterialExpressionRebirthSurfaceOutput::UMaterialExpressionRebirthSurfaceOutput(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
    MenuCategories.Add(FText::FromString(TEXT("Rebirth")));
    bCollapsed = true;
    Outputs.Reset();
    NormalWS.InputName = TEXT("NormalWS");
    Roughness.InputName = TEXT("Roughness");
    MaterialAO.InputName = TEXT("MaterialAO");
    SurfaceDiffusion.InputName = TEXT("SurfaceDiffusion");
    Sentinel.InputName = TEXT("Sentinel");
#endif
}

#if WITH_EDITOR
int32 UMaterialExpressionRebirthSurfaceOutput::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
    FExpressionInput* Input = GetInput(OutputIndex);
    if (!Input || !Input->GetTracedInput().Expression)
    {
        return CompilerError(Compiler, TEXT("Rebirth Surface Data requires all five original surface inputs"));
    }
    return Compiler->CustomOutput(this, OutputIndex, Input->Compile(Compiler));
}

void UMaterialExpressionRebirthSurfaceOutput::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Rebirth Surface Data"));
}

FExpressionInput* UMaterialExpressionRebirthSurfaceOutput::GetInput(int32 InputIndex)
{
    switch (InputIndex)
    {
    case 0: return &NormalWS;
    case 1: return &Roughness;
    case 2: return &MaterialAO;
    case 3: return &SurfaceDiffusion;
    case 4: return &Sentinel;
    default: return nullptr;
    }
}
#endif
