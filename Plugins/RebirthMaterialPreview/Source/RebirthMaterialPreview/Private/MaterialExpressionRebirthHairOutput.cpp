#include "MaterialExpressionRebirthHairOutput.h"
#include "MaterialCompiler.h"

UMaterialExpressionRebirthHairOutput::UMaterialExpressionRebirthHairOutput(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
    MenuCategories.Add(FText::FromString(TEXT("Rebirth")));
    bCollapsed = true;
    Outputs.Reset();
    EncodedWideBentNormal.InputName = TEXT("EncodedWideBentNormal");
#endif
}

#if WITH_EDITOR
int32 UMaterialExpressionRebirthHairOutput::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
    if (OutputIndex != 0 || !EncodedWideBentNormal.GetTracedInput().Expression)
    {
        return CompilerError(Compiler, TEXT("Rebirth Hair Data requires an encoded world-space wide bent normal"));
    }
    return Compiler->CustomOutput(this, OutputIndex, EncodedWideBentNormal.Compile(Compiler));
}

void UMaterialExpressionRebirthHairOutput::GetCaption(TArray<FString>& OutCaptions) const
{
    OutCaptions.Add(TEXT("Rebirth Hair Data"));
}

FExpressionInput* UMaterialExpressionRebirthHairOutput::GetInput(int32 InputIndex)
{
    return InputIndex == 0 ? &EncodedWideBentNormal : nullptr;
}
#endif
