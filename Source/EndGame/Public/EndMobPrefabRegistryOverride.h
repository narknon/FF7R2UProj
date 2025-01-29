#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEndMobPrefabFitGroundType.h"
#include "EWeaponSlot.h"
#include "EndMobPrefabBoneControlRegistryOverride.h"
#include "Templates/SubclassOf.h"
#include "EndMobPrefabRegistryOverride.generated.h"

class AEndCharacterBase;
class AEndSkeletalMeshActorBase;
class UEndAssetDataAsset;

USTRUCT(BlueprintType)
struct FEndMobPrefabRegistryOverride {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CharaSpecID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<UEndAssetDataAsset> CharaSpecDataAsset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftClassPtr<AEndCharacterBase> CharacterClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector OffsetTranslation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator OffsetRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverrideFitGroundType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMobPrefabFitGroundType FitGroundType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EWeaponSlot, FName> AccessorIds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, float> LookAtTargetList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EWeaponSlot, TSoftClassPtr<AEndSkeletalMeshActorBase>> InstanceOverrideWeapons;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EWeaponSlot, TSubclassOf<AEndSkeletalMeshActorBase>> OverrideWeapons;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMobPrefabBoneControlRegistryOverride> BoneControls;
    
    ENDGAME_API FEndMobPrefabRegistryOverride();
};

