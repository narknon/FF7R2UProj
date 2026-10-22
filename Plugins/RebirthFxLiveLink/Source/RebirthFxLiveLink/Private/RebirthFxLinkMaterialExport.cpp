#include "RebirthFxLinkLibrary.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Engine/Texture.h"
#include "HAL/FileManager.h"
#include "MaterialCachedData.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialParameterCollection.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "RHI.h"
#include "RenderingThread.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthMaterialExport, Log, All);

namespace RebirthMaterialExportDetail
{
	template <typename TEnum>
	FString EnumName(TEnum Value)
	{
		const UEnum* Enum = StaticEnum<TEnum>();
		return Enum ? Enum->GetNameStringByValue(static_cast<int64>(Value)) : FString::FromInt(static_cast<int32>(Value));
	}

	TSharedPtr<FJsonValue> Number(double Value)
	{
		return MakeShared<FJsonValueNumber>(Value);
	}

	TSharedPtr<FJsonValue> Text(const FString& Value)
	{
		return MakeShared<FJsonValueString>(Value);
	}

	const TCHAR* TextureTypeName(EMaterialTextureParameterType Type)
	{
		switch (Type)
		{
		case EMaterialTextureParameterType::Standard2D: return TEXT("Texture2D");
		case EMaterialTextureParameterType::Cube: return TEXT("TextureCube");
		case EMaterialTextureParameterType::Array2D: return TEXT("Texture2DArray");
		case EMaterialTextureParameterType::Volume: return TEXT("VolumeTexture");
		case EMaterialTextureParameterType::Virtual: return TEXT("VirtualTexture");
		default: return TEXT("?");
		}
	}

	/** The collection with this state id: one the material lists, else any loaded one. */
	UMaterialParameterCollection* FindCollection(const UMaterial* Base, const FGuid& StateId)
	{
		for (const FMaterialParameterCollectionInfo& Info : Base->GetCachedExpressionData().ParameterCollectionInfos)
		{
			if (Info.ParameterCollection && Info.ParameterCollection->StateId == StateId)
			{
				return Info.ParameterCollection;
			}
		}
		for (TObjectIterator<UMaterialParameterCollection> It; It; ++It)
		{
			if (It->StateId == StateId)
			{
				return *It;
			}
		}
		return nullptr;
	}
}

FString URebirthFxLinkLibrary::ExportMaterialForGame(UMaterialInterface* MaterialInterface, const FString& Directory)
{
	using namespace RebirthMaterialExportDetail;

	if (!MaterialInterface)
	{
		return TEXT("no material given");
	}
	UMaterial* Base = MaterialInterface->GetMaterial();
	if (!Base)
	{
		return TEXT("the material has no base material");
	}
	const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
	FMaterialResource* Resource = MaterialInterface->GetMaterialResource(FeatureLevel);
	if (!Resource)
	{
		return TEXT("the material has no resource for this editor's feature level");
	}
	Resource->FinishCompilation();
	FMaterialShaderMap* ShaderMap = Resource->GetGameThreadShaderMap();
	if (!ShaderMap)
	{
		return TEXT("the material did not compile: open it in the material editor to see why");
	}

	// The code: the material template filled in by this editor's own material translator.
	FString Source;
	if (!Resource->GetMaterialExpressionSource(Source))
	{
		return TEXT("the editor could not translate the material (open it in the material editor to see the errors)");
	}

	// The constants of its Material uniform buffer, evaluated for this material or instance (on the rendering thread,
	// as the renderer does it), and the parameter collections the code reads, in the code's order.
	const FUniformExpressionSet& Set = ShaderMap->GetUniformExpressionSet();
	const FRHIUniformBufferLayout& Layout = Set.GetUniformBufferLayout();
	TArray<uint8> Buffer;
	Buffer.SetNumZeroed(Align(FMath::Max<uint32>(Layout.ConstantBufferSize, 16u), 16u));
	TArray<FGuid> CollectionIds;
	bool bEvaluated = false;
	FlushRenderingCommands();
	const FMaterialRenderProxy* Proxy = MaterialInterface->GetRenderProxy();
	if (Proxy && Layout.ConstantBufferSize > 0)
	{
		uint8* BufferData = Buffer.GetData();
		const int32 BufferSize = Buffer.Num();
		ENQUEUE_RENDER_COMMAND(RebirthEvaluateMaterialUniforms)([Proxy, Resource, BufferData, BufferSize, &CollectionIds, &bEvaluated](FRHICommandListImmediate&)
		{
			const FMaterialShaderMap* RenderingMap = Resource->GetRenderingThreadShaderMap();
			if (!RenderingMap)
			{
				return;
			}
			FMaterialRenderContext Context(Proxy, *Resource, nullptr);
			FUniformExpressionCache Cache;
			Proxy->EvaluateUniformExpressions(Cache, Context);
			RenderingMap->GetUniformExpressionSet().FillUniformBuffer(Context, Cache, BufferData, BufferSize);
			CollectionIds = Cache.ParameterCollections;
			bEvaluated = true;
		});
		FlushRenderingCommands();
	}

	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("tool"), TEXT("RebirthFxLiveLink ExportMaterialForGame 1"));
	Root->SetStringField(TEXT("material"), MaterialInterface->GetPathName());
	Root->SetStringField(TEXT("class"), MaterialInterface->GetClass()->GetName());
	Root->SetStringField(TEXT("base_material"), Base->GetPathName());
	Root->SetStringField(TEXT("feature_level"), FString::FromInt(static_cast<int32>(FeatureLevel)));
	Root->SetStringField(TEXT("shader_format"), LegacyShaderPlatformToShaderFormat(GMaxRHIShaderPlatform).ToString());
	Root->SetStringField(TEXT("domain"), EnumName(Resource->GetMaterialDomain()));
	Root->SetStringField(TEXT("blend_mode"), EnumName(Resource->GetBlendMode()));
	{
		const FMaterialShadingModelField Models = Resource->GetShadingModels();
		Root->SetNumberField(TEXT("shading_model_bits"), Models.GetShadingModelField());
		TArray<TSharedPtr<FJsonValue>> Names;
		for (int32 Model = 0; Model < MSM_NUM; ++Model)
		{
			if (Models.HasShadingModel(static_cast<EMaterialShadingModel>(Model)))
			{
				Names.Add(Text(EnumName(static_cast<EMaterialShadingModel>(Model))));
			}
		}
		Root->SetArrayField(TEXT("shading_models"), Names);
	}
	Root->SetBoolField(TEXT("two_sided"), Resource->IsTwoSided());
	Root->SetBoolField(TEXT("masked"), Resource->IsMasked());
	Root->SetNumberField(TEXT("opacity_mask_clip_value"), Resource->GetOpacityMaskClipValue());
	Root->SetBoolField(TEXT("tangent_space_normal"), Resource->IsTangentSpaceNormal());
	Root->SetBoolField(TEXT("use_material_attributes"), Base->bUseMaterialAttributes != 0);

	// uniform buffer: constants (floats, before the first resource member) and layout
	{
		uint32 FirstResource = Layout.ConstantBufferSize;
		for (int32 ResourceIndex = 0; ResourceIndex < Layout.Resources.Num(); ++ResourceIndex)
		{
			FirstResource = FMath::Min<uint32>(FirstResource, Layout.Resources[ResourceIndex].MemberOffset);
		}
		TSharedRef<FJsonObject> Uniform = MakeShared<FJsonObject>();
		Uniform->SetNumberField(TEXT("buffer_size"), Layout.ConstantBufferSize);
		Uniform->SetNumberField(TEXT("constants_size"), FirstResource);
		Uniform->SetNumberField(TEXT("resources"), Layout.Resources.Num());
		Uniform->SetBoolField(TEXT("evaluated"), bEvaluated);
		TArray<TSharedPtr<FJsonValue>> Floats;
		for (uint32 Offset = 0; Offset + 4 <= FirstResource && Offset + 4 <= static_cast<uint32>(Buffer.Num()); Offset += 4)
		{
			float Value;
			FMemory::Memcpy(&Value, Buffer.GetData() + Offset, sizeof(Value));
			Floats.Add(Number(FMath::IsFinite(Value) ? Value : 0.0));
		}
		Uniform->SetArrayField(TEXT("constants"), Floats);
		Root->SetObjectField(TEXT("uniform"), Uniform);
	}

	// textures, per type in the code's order (Material.Texture2D_<n> is the n-th Texture2D)
	{
		TArray<TSharedPtr<FJsonValue>> Textures;
		for (uint32 TypeIndex = 0; TypeIndex < NumMaterialTextureParameterTypes; ++TypeIndex)
		{
			const EMaterialTextureParameterType Type = static_cast<EMaterialTextureParameterType>(TypeIndex);
			for (int32 Index = 0; Index < Set.GetNumTextures(Type); ++Index)
			{
				const FMaterialTextureParameterInfo& Parameter = Set.GetTextureParameter(Type, Index);
				UTexture* Texture = nullptr;
				Set.GetGameThreadTextureValue(Type, Index, MaterialInterface, *Resource, Texture);
				TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
				Entry->SetStringField(TEXT("type"), TextureTypeName(Type));
				Entry->SetNumberField(TEXT("index"), Index);
				Entry->SetStringField(TEXT("parameter"), Parameter.GetParameterName().ToString());
				Entry->SetNumberField(TEXT("texture_index"), Parameter.TextureIndex);
				Entry->SetStringField(TEXT("sampler_source"), EnumName(static_cast<ESamplerSourceMode>(Parameter.SamplerSource.GetValue())));
				if (Texture)
				{
					Entry->SetStringField(TEXT("texture"), Texture->GetPathName());
					Entry->SetStringField(TEXT("texture_class"), Texture->GetClass()->GetName());
					Entry->SetBoolField(TEXT("srgb"), Texture->SRGB != 0);
					Entry->SetStringField(TEXT("compression"), EnumName(Texture->CompressionSettings.GetValue()));
					Entry->SetNumberField(TEXT("width"), Texture->GetSurfaceWidth());
					Entry->SetNumberField(TEXT("height"), Texture->GetSurfaceHeight());
				}
				Textures.Add(MakeShared<FJsonValueObject>(Entry));
			}
		}
		Root->SetArrayField(TEXT("textures"), Textures);
	}

	// parameter collections: MaterialCollection<n> is the n-th
	{
		TArray<TSharedPtr<FJsonValue>> Collections;
		for (int32 Index = 0; Index < CollectionIds.Num(); ++Index)
		{
			TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
			Entry->SetNumberField(TEXT("index"), Index);
			Entry->SetStringField(TEXT("state_id"), CollectionIds[Index].ToString());
			if (UMaterialParameterCollection* Collection = FindCollection(Base, CollectionIds[Index]))
			{
				Entry->SetStringField(TEXT("collection"), Collection->GetPathName());
				TArray<TSharedPtr<FJsonValue>> Scalars, Vectors;
				for (const FCollectionScalarParameter& Scalar : Collection->ScalarParameters)
				{
					TSharedRef<FJsonObject> P = MakeShared<FJsonObject>();
					P->SetStringField(TEXT("name"), Scalar.ParameterName.ToString());
					P->SetNumberField(TEXT("value"), Scalar.DefaultValue);
					Scalars.Add(MakeShared<FJsonValueObject>(P));
				}
				for (const FCollectionVectorParameter& Vector : Collection->VectorParameters)
				{
					TSharedRef<FJsonObject> P = MakeShared<FJsonObject>();
					P->SetStringField(TEXT("name"), Vector.ParameterName.ToString());
					P->SetArrayField(TEXT("value"), { Number(Vector.DefaultValue.R), Number(Vector.DefaultValue.G), Number(Vector.DefaultValue.B), Number(Vector.DefaultValue.A) });
					Vectors.Add(MakeShared<FJsonValueObject>(P));
				}
				Entry->SetArrayField(TEXT("scalars"), Scalars);
				Entry->SetArrayField(TEXT("vectors"), Vectors);
			}
			Collections.Add(MakeShared<FJsonValueObject>(Entry));
		}
		Root->SetArrayField(TEXT("parameter_collections"), Collections);
	}

	FString Json;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
		FJsonSerializer::Serialize(Root, Writer);
	}
	IFileManager::Get().MakeDirectory(*Directory, true);
	const FString HlslFile = Directory / TEXT("material.hlsl");
	const FString JsonFile = Directory / TEXT("material.json");
	if (!FFileHelper::SaveStringToFile(Source, *HlslFile, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		return TEXT("could not write ") + HlslFile;
	}
	if (!FFileHelper::SaveStringToFile(Json, *JsonFile, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		return TEXT("could not write ") + JsonFile;
	}
	UE_LOG(LogRebirthMaterialExport, Log, TEXT("%s -> %s (%d bytes of code, uniforms %s)"), *MaterialInterface->GetPathName(), *Directory, Source.Len(),
		bEvaluated ? TEXT("evaluated") : TEXT("not evaluated"));
	return FString();
}
