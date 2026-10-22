#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialLayersFunctions.h"
#include "UObject/Object.h"
#include "RebirthMaterialInstanceOverrides.generated.h"

class UMaterialInstanceConstant;
class UTexture;

USTRUCT(BlueprintType)
struct REBIRTHMATERIALPREVIEW_API FRebirthScalarMaterialOverride
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) FName Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) TEnumAsByte<EMaterialParameterAssociation> Association = GlobalParameter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) int32 Index = INDEX_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter) bool bOverride = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bOverride")) float Value = 0.0f;
};

USTRUCT(BlueprintType)
struct REBIRTHMATERIALPREVIEW_API FRebirthVectorMaterialOverride
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) FName Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) TEnumAsByte<EMaterialParameterAssociation> Association = GlobalParameter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) int32 Index = INDEX_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter) bool bOverride = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bOverride")) FLinearColor Value = FLinearColor::Black;
};

USTRUCT(BlueprintType)
struct REBIRTHMATERIALPREVIEW_API FRebirthTextureMaterialOverride
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) FName Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) TEnumAsByte<EMaterialParameterAssociation> Association = GlobalParameter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parameter) int32 Index = INDEX_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter) bool bOverride = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bOverride")) UTexture* Value = nullptr;
};

/** Edits uniform own-array entries without constructing UMaterialEditorInstanceConstant. */
UCLASS(Transient, BlueprintType)
class REBIRTHMATERIALPREVIEW_API URebirthMaterialInstanceOverrides : public UObject
{
	GENERATED_BODY()

public:
	URebirthMaterialInstanceOverrides();

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Scalars, meta = (TitleProperty = "Name"))
	TArray<FRebirthScalarMaterialOverride> Scalars;
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Vectors, meta = (TitleProperty = "Name"))
	TArray<FRebirthVectorMaterialOverride> Vectors;
	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Textures, meta = (TitleProperty = "Name"))
	TArray<FRebirthTextureMaterialOverride> Textures;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Status)
	FString LastError;

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Materials")
	bool Initialize(UMaterialInstanceConstant* InSource);
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Materials")
	bool InitializeFromInstance(UMaterialInstanceConstant* InSource) { return Initialize(InSource); }
	/** Discards pending model edits and reads the current own overrides/effective inherited values. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Materials")
	bool RefreshFromSource();
	/** Applies only entries changed from the model baseline; no implicit parent values are copied. */
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Materials")
	bool ApplyChanges();
	UFUNCTION(BlueprintPure, Category = "Rebirth|Materials")
	UMaterialInstanceConstant* GetSource() const { return Source; }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditUndo() override;
#endif

private:
	enum EKindMask : uint8 { ScalarKind = 1, VectorKind = 2, TextureKind = 4, AllKinds = 7 };
	bool ApplyKinds(uint8 Kinds);
	bool ValidateSource(FString& OutError) const;
	bool bSynchronizing = false;

	UPROPERTY(Transient) UMaterialInstanceConstant* Source;
	UPROPERTY(Transient) class UMaterialInterface* InitializedParent;
	UPROPERTY(Transient) TArray<FMaterialParameterInfo> ScalarInfos;
	UPROPERTY(Transient) TArray<FMaterialParameterInfo> VectorInfos;
	UPROPERTY(Transient) TArray<FMaterialParameterInfo> TextureInfos;
	UPROPERTY(Transient) TArray<FRebirthScalarMaterialOverride> ScalarBaseline;
	UPROPERTY(Transient) TArray<FRebirthVectorMaterialOverride> VectorBaseline;
	UPROPERTY(Transient) TArray<FRebirthTextureMaterialOverride> TextureBaseline;
};
