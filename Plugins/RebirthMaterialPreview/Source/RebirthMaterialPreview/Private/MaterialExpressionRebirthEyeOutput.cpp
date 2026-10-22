#include "MaterialExpressionRebirthEyeOutput.h"
#include "MaterialCompiler.h"

UMaterialExpressionRebirthEyeOutput::UMaterialExpressionRebirthEyeOutput(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
    MenuCategories.Add(NSLOCTEXT("RebirthMaterialPreview", "Rebirth", "Rebirth"));
    Outputs.Reset();
#endif
}

#if WITH_EDITOR
int32 UMaterialExpressionRebirthEyeOutput::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
    FExpressionInput* Input = GetInput(OutputIndex);
    if (!Input || !Input->GetTracedInput().Expression)
    {
        return CompilerError(Compiler, TEXT("Recovered Rebirth Eye requires all six surface inputs"));
    }
    const int32 Value = Input->Compile(Compiler);
    if (Value == INDEX_NONE)
    {
        return INDEX_NONE;
    }
    return Compiler->CustomOutput(this, OutputIndex, Compiler->ForceCast(Value, static_cast<EMaterialValueType>(GetInputType(OutputIndex))));
}

void UMaterialExpressionRebirthEyeOutput::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Recovered Rebirth Eye Surface"));
}

const TArray<FExpressionInput*> UMaterialExpressionRebirthEyeOutput::GetInputs()
{
    return { &ScleraNormalWS, &RadialDirectionWS, &IrisNormalPacked, &ScleraMask, &IrisOcclusion, &RadialDistance };
}

FExpressionInput* UMaterialExpressionRebirthEyeOutput::GetInput(int32 InputIndex)
{
    switch (InputIndex)
    {
    case 0: return &ScleraNormalWS;
    case 1: return &RadialDirectionWS;
    case 2: return &IrisNormalPacked;
    case 3: return &ScleraMask;
    case 4: return &IrisOcclusion;
    case 5: return &RadialDistance;
    default: return nullptr;
    }
}

FName UMaterialExpressionRebirthEyeOutput::GetInputName(int32 InputIndex) const
{
    static const FName Names[] = { TEXT("ScleraNormalWS"), TEXT("RadialDirectionWS"), TEXT("IrisNormalPacked"), TEXT("ScleraMask"), TEXT("IrisOcclusion"), TEXT("RadialDistance") };
    return InputIndex >= 0 && InputIndex < UE_ARRAY_COUNT(Names) ? Names[InputIndex] : NAME_None;
}

uint32 UMaterialExpressionRebirthEyeOutput::GetInputType(int32 InputIndex)
{
    return InputIndex < 2 ? MCT_Float3 : MCT_Float1;
}
#endif
