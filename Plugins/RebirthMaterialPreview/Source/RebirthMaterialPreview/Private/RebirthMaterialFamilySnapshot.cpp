#include "RebirthMaterialFamilySnapshot.h"

#include "Dom/JsonObject.h"
#include "Engine/Font.h"
#include "Engine/Texture.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialExpressionTextureBase.h"
#include "Materials/MaterialFunctionInterface.h"
#include "ShaderResourceBuffer.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"
#include "VT/RuntimeVirtualTexture.h"

namespace RebirthMaterialFamilySnapshot
{
    namespace
    {
        constexpr int32 MaxDepth = 64;
        constexpr int32 MaxEntries = 4096;

        FString ToString(const TSharedRef<FJsonObject>& Value)
        {
            FString Text;
            const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);
            FJsonSerializer::Serialize(Value, Writer);
            return Text;
        }

        FString Key(const FMaterialParameterInfo& Info)
        {
            return FString::Printf(TEXT("%d:%d:%s"), static_cast<int32>(Info.Association), Info.Index, *Info.Name.ToString());
        }

        TSharedRef<FJsonObject> Identity(const FMaterialParameterInfo& Info)
        {
            const TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
            Row->SetStringField(TEXT("name"), Info.Name.ToString());
            Row->SetNumberField(TEXT("association"), static_cast<int32>(Info.Association));
            Row->SetNumberField(TEXT("index"), Info.Index);
            Row->SetStringField(TEXT("identity"), Key(Info));
            return Row;
        }

        void Put(TMap<FString, FMaterialParameterInfo>& Infos, const FMaterialParameterInfo& Info)
        {
            Infos.Add(Key(Info), Info);
        }

        template<typename RowType>
        bool Bounded(const TArray<RowType>& Rows) { return Rows.Num() <= MaxEntries; }
    }

    FString Inspect(UMaterialInterface* Material)
    {
        const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
        Report->SetBoolField(TEXT("success"), false);
        Report->SetBoolField(TEXT("mutates_original"), false);
        auto Fail = [&Report](const FString& Reason)
        {
            Report->SetStringField(TEXT("reason"), Reason);
            return ToString(Report);
        };
        if (!IsInGameThread() || !IsValid(Material)) { return Fail(TEXT("valid_material_on_game_thread_required")); }
        Report->SetStringField(TEXT("original_object_path"), Material->GetPathName());

        TArray<UMaterialInstance*> Chain;
        TSet<UMaterialInterface*> Seen;
        TArray<TSharedPtr<FJsonValue>> Parents;
        UMaterialInterface* Current = Material;
        UMaterial* Base = nullptr;
        bool bCooked = false;
        while (Current)
        {
            if (!IsValid(Current) || Current->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad | RF_NeedPostLoadSubobjects | RF_BeginDestroyed | RF_FinishDestroyed) ||
                Seen.Contains(Current) || Seen.Num() >= MaxDepth) { return Fail(TEXT("invalid_parent_chain")); }
            Seen.Add(Current);
            Parents.Add(MakeShared<FJsonValueString>(Current->GetPathName()));
            const UPackage* Package = Current->GetOutermost();
            bCooked |= Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
            if (UMaterialInstance* MI = Cast<UMaterialInstance>(Current)) { Chain.Add(MI); Current = MI->Parent; }
            else { Base = Cast<UMaterial>(Current); break; }
        }
        if (!Base) { return Fail(TEXT("no_supported_base_material")); }
        Report->SetArrayField(TEXT("parent_chain"), Parents);
        Report->SetBoolField(TEXT("uses_cooked_chain"), bCooked);
        Report->SetStringField(TEXT("base_material"), Base->GetPathName());
        const int32 Domain = static_cast<int32>(Base->MaterialDomain.GetValue());
        const int32 Blend = static_cast<int32>(Material->GetBlendMode());
        if (Domain < 0 || Domain >= MD_MAX || Blend < 0 || Blend >= BLEND_MAX || !Material->GetShadingModels().IsValid())
        { return Fail(TEXT("unsupported_native_domain_blend_or_shading_model")); }
        Report->SetNumberField(TEXT("domain"), Domain);
        Report->SetNumberField(TEXT("blend_mode"), Blend);
        Report->SetBoolField(TEXT("two_sided"), Material->IsTwoSided());
        Report->SetNumberField(TEXT("opacity_mask_clip"), Material->GetOpacityMaskClipValue());

        TMap<FString, FMaterialParameterInfo> ScalarInfos, VectorInfos, TextureInfos, FontInfos, RVTInfos, BufferInfos;
        TMap<FString, TSharedPtr<FJsonValue>> Switches, Masks, Terrain, Layers;
        TArray<TSharedPtr<FJsonValue>> ChainDetails;
        bool bOtherStatic = false, bNonUniform = false;
        // Visit root instance first, then apply descendant static overrides.
        for (int32 I = Chain.Num() - 1; I >= 0; --I)
        {
            UMaterialInstance* MI = Chain[I];
            const FStaticParameterSet& Static = MI->GetStaticParameters();
            if (!Bounded(MI->ScalarParameterValues) || !Bounded(MI->VectorParameterValues) || !Bounded(MI->TextureParameterValues) ||
                !Bounded(MI->FontParameterValues) || !Bounded(MI->RuntimeVirtualTextureParameterValues) || !Bounded(MI->ShaderResourceBufferParameterValues) ||
                !Bounded(Static.StaticSwitchParameters) || !Bounded(Static.StaticComponentMaskParameters) ||
                !Bounded(Static.TerrainLayerWeightParameters) || !Bounded(Static.MaterialLayersParameters)) { return Fail(TEXT("parameter_count_limit")); }
            for (const FScalarParameterValue& Row : MI->ScalarParameterValues) { Put(ScalarInfos, Row.ParameterInfo); }
            for (const FVectorParameterValue& Row : MI->VectorParameterValues) { Put(VectorInfos, Row.ParameterInfo); }
            for (const FTextureParameterValue& Row : MI->TextureParameterValues) { Put(TextureInfos, Row.ParameterInfo); }
            for (const FFontParameterValue& Row : MI->FontParameterValues) { Put(FontInfos, Row.ParameterInfo); }
            for (const FRuntimeVirtualTextureParameterValue& Row : MI->RuntimeVirtualTextureParameterValues) { Put(RVTInfos, Row.ParameterInfo); }
            for (const FShaderResourceBufferParameterValue& Row : MI->ShaderResourceBufferParameterValues) { Put(BufferInfos, Row.ParameterInfo); }
            const TSharedRef<FJsonObject> ChainRow = MakeShared<FJsonObject>();
            ChainRow->SetStringField(TEXT("path"), MI->GetPathName());
            ChainRow->SetBoolField(TEXT("has_static_permutation_resource"), MI->bHasStaticPermutationResource);
            ChainRow->SetBoolField(TEXT("has_overridden_base_properties"), MI->HasOverridenBaseProperties());
            ChainRow->SetNumberField(TEXT("own_scalar_count"), MI->ScalarParameterValues.Num());
            ChainRow->SetNumberField(TEXT("own_vector_count"), MI->VectorParameterValues.Num());
            ChainRow->SetNumberField(TEXT("own_texture_count"), MI->TextureParameterValues.Num());
            ChainRow->SetNumberField(TEXT("own_static_switch_count"), Static.StaticSwitchParameters.Num());
            ChainDetails.Add(MakeShared<FJsonValueObject>(ChainRow));
            for (const FStaticSwitchParameter& Row : Static.StaticSwitchParameters)
            {
                if (!Row.bOverride) { continue; }
                const TSharedRef<FJsonObject> Entry = Identity(Row.ParameterInfo);
                Entry->SetBoolField(TEXT("value"), Row.Value);
                Switches.Add(Key(Row.ParameterInfo), MakeShared<FJsonValueObject>(Entry));
            }
            for (const FStaticComponentMaskParameter& Row : Static.StaticComponentMaskParameters)
            {
                if (!Row.bOverride) { continue; }
                const TSharedRef<FJsonObject> Entry = Identity(Row.ParameterInfo);
                Entry->SetBoolField(TEXT("r"), Row.R); Entry->SetBoolField(TEXT("g"), Row.G);
                Entry->SetBoolField(TEXT("b"), Row.B); Entry->SetBoolField(TEXT("a"), Row.A);
                Masks.Add(Key(Row.ParameterInfo), MakeShared<FJsonValueObject>(Entry));
            }
            for (const FStaticTerrainLayerWeightParameter& Row : Static.TerrainLayerWeightParameters)
            {
                if (!Row.bOverride) { continue; }
                const TSharedRef<FJsonObject> Entry = Identity(Row.ParameterInfo);
                Entry->SetNumberField(TEXT("weightmap_index"), Row.WeightmapIndex);
                Entry->SetBoolField(TEXT("weight_based_blend"), Row.bWeightBasedBlend);
                Terrain.Add(Key(Row.ParameterInfo), MakeShared<FJsonValueObject>(Entry));
            }
            for (const FStaticMaterialLayersParameter& Row : Static.MaterialLayersParameters)
            {
                if (!Row.bOverride) { continue; }
                if (!Bounded(Row.Value.Layers) || !Bounded(Row.Value.Blends) || !Bounded(Row.Value.LayerStates)) { return Fail(TEXT("material_layer_count_limit")); }
                const TSharedRef<FJsonObject> Entry = Identity(Row.ParameterInfo);
                TArray<TSharedPtr<FJsonValue>> Functions, Blends, States;
                for (UMaterialFunctionInterface* Function : Row.Value.Layers)
                    Functions.Add(MakeShared<FJsonValueString>(IsValid(Function) ? Function->GetPathName() : FString()));
                for (UMaterialFunctionInterface* Function : Row.Value.Blends)
                    Blends.Add(MakeShared<FJsonValueString>(IsValid(Function) ? Function->GetPathName() : FString()));
                for (bool State : Row.Value.LayerStates) { States.Add(MakeShared<FJsonValueBoolean>(State)); }
                Entry->SetArrayField(TEXT("layers"), Functions); Entry->SetArrayField(TEXT("blends"), Blends);
                Entry->SetArrayField(TEXT("layer_states"), States);
                Layers.Add(Key(Row.ParameterInfo), MakeShared<FJsonValueObject>(Entry));
            }
            bOtherStatic |= Static.StaticComponentMaskParameters.Num() || Static.TerrainLayerWeightParameters.Num() || Static.MaterialLayersParameters.Num();
            bNonUniform |= MI->FontParameterValues.Num() || MI->RuntimeVirtualTextureParameterValues.Num() || MI->ShaderResourceBufferParameterValues.Num();
        }
        if (ScalarInfos.Num() > MaxEntries || VectorInfos.Num() > MaxEntries || TextureInfos.Num() > MaxEntries || Switches.Num() > MaxEntries ||
            FontInfos.Num() > MaxEntries || RVTInfos.Num() > MaxEntries || BufferInfos.Num() > MaxEntries ||
            Masks.Num() > MaxEntries || Terrain.Num() > MaxEntries || Layers.Num() > MaxEntries)
        { return Fail(TEXT("effective_parameter_count_limit")); }
        TArray<TSharedPtr<FJsonValue>> StaticRows, ScalarRows, VectorRows, TextureRows, MaskRows, TerrainRows, LayerRows, FontRows, RVTRows, BufferRows;
        TArray<FString> Keys;
        Switches.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys) { StaticRows.Add(Switches[Name]); }
        Masks.GetKeys(Keys); Keys.Sort(); for (const FString& Name : Keys) { MaskRows.Add(Masks[Name]); }
        Terrain.GetKeys(Keys); Keys.Sort(); for (const FString& Name : Keys) { TerrainRows.Add(Terrain[Name]); }
        Layers.GetKeys(Keys); Keys.Sort(); for (const FString& Name : Keys) { LayerRows.Add(Layers[Name]); }
        ScalarInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = ScalarInfos[Name];
            float Value = 0.0f;
            if (!Material->GetScalarParameterValue(FHashedMaterialParameterInfo(Info), Value) || !FMath::IsFinite(Value))
            { return Fail(TEXT("invalid_effective_scalar:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info); Row->SetNumberField(TEXT("value"), Value);
            ScalarRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        VectorInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = VectorInfos[Name];
            FLinearColor Value;
            if (!Material->GetVectorParameterValue(FHashedMaterialParameterInfo(Info), Value) ||
                !FMath::IsFinite(Value.R) || !FMath::IsFinite(Value.G) || !FMath::IsFinite(Value.B) || !FMath::IsFinite(Value.A))
            { return Fail(TEXT("invalid_effective_vector:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info);
            TArray<TSharedPtr<FJsonValue>> Channels;
            for (float Channel : {Value.R, Value.G, Value.B, Value.A}) { Channels.Add(MakeShared<FJsonValueNumber>(Channel)); }
            Row->SetArrayField(TEXT("value"), Channels); VectorRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        TextureInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = TextureInfos[Name];
            UTexture* Value = nullptr;
            if (!Material->GetTextureParameterValue(FHashedMaterialParameterInfo(Info), Value) || (Value && !IsValid(Value)))
            { return Fail(TEXT("invalid_effective_texture:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info);
            Row->SetStringField(TEXT("value"), Value ? Value->GetPathName() : FString());
            Row->SetStringField(TEXT("class"), Value ? Value->GetClass()->GetName() : FString());
            if (Value)
            {
                Row->SetNumberField(TEXT("material_type"), static_cast<int32>(Value->GetMaterialType()));
                Row->SetNumberField(TEXT("sampler_type"), static_cast<int32>(UMaterialExpressionTextureBase::GetSamplerTypeForTexture(Value)));
                Row->SetBoolField(TEXT("srgb"), Value->SRGB);
            }
            TextureRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        FontInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = FontInfos[Name];
            UFont* Value = nullptr; int32 Page = 0;
            if (!Material->GetFontParameterValue(FHashedMaterialParameterInfo(Info), Value, Page) || (Value && !IsValid(Value)))
            { return Fail(TEXT("invalid_effective_font:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info);
            Row->SetStringField(TEXT("value"), Value ? Value->GetPathName() : FString()); Row->SetNumberField(TEXT("page"), Page);
            FontRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        RVTInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = RVTInfos[Name];
            URuntimeVirtualTexture* Value = nullptr;
            if (!Material->GetRuntimeVirtualTextureParameterValue(FHashedMaterialParameterInfo(Info), Value) || (Value && !IsValid(Value)))
            { return Fail(TEXT("invalid_effective_rvt:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info); Row->SetStringField(TEXT("value"), Value ? Value->GetPathName() : FString());
            RVTRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        BufferInfos.GetKeys(Keys); Keys.Sort();
        for (const FString& Name : Keys)
        {
            const FMaterialParameterInfo& Info = BufferInfos[Name];
            UShaderResourceBuffer* Value = nullptr;
            if (!Material->GetShaderResourceBufferParameterValue(FHashedMaterialParameterInfo(Info), Value) || (Value && !IsValid(Value)))
            { return Fail(TEXT("invalid_effective_shader_buffer:") + Info.Name.ToString()); }
            const TSharedRef<FJsonObject> Row = Identity(Info); Row->SetStringField(TEXT("value"), Value ? Value->GetPathName() : FString());
            BufferRows.Add(MakeShared<FJsonValueObject>(Row));
        }
        Report->SetArrayField(TEXT("static_switches"), StaticRows);
        Report->SetArrayField(TEXT("static_component_masks"), MaskRows);
        Report->SetArrayField(TEXT("static_terrain_layers"), TerrainRows);
        Report->SetArrayField(TEXT("static_material_layers"), LayerRows);
        Report->SetArrayField(TEXT("instance_chain_details_root_first"), ChainDetails);
        Report->SetBoolField(TEXT("has_non_switch_static_parameters"), bOtherStatic);
        Report->SetBoolField(TEXT("has_font_rvt_or_shader_buffer_parameters"), bNonUniform);
        Report->SetArrayField(TEXT("scalars"), ScalarRows);
        Report->SetArrayField(TEXT("vectors"), VectorRows);
        Report->SetArrayField(TEXT("textures"), TextureRows);
        Report->SetArrayField(TEXT("fonts"), FontRows);
        Report->SetArrayField(TEXT("runtime_virtual_textures"), RVTRows);
        Report->SetArrayField(TEXT("shader_resource_buffers"), BufferRows);
        Report->SetBoolField(TEXT("enumeration_complete_for_serialized_instance_chain"), true);
        Report->SetBoolField(TEXT("base_expression_defaults_enumerated"), false);
        Report->SetBoolField(TEXT("success"), true);
        return ToString(Report);
    }
}
