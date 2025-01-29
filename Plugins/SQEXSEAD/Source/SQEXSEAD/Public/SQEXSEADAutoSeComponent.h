#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SQEXSEADAutoSeComponent.generated.h"

class UPawnMovementComponent;
class USQEXSEADAutoSeComponentAssetTable;
class USQEXSEADAutoSeComponentCallback;
class USQEXSEADAutoSeComponentSetting;
class USQEXSEADAutoSeDetectionSetting;
class USQEXSEADAutoSeProcessorLODSettings;
class USkeletalMeshComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class SQEXSEAD_API USQEXSEADAutoSeComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeComponentCallback* AutoSeCallback;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeComponentSetting* SettingData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeComponentAssetTable* AssetTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeDetectionSetting* DetectionSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADAutoSeProcessorLODSettings* ProcLodSetting;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* CachedMeshReference;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UPawnMovementComponent* CachedMovementComponent;
    
public:
    USQEXSEADAutoSeComponent(const FObjectInitializer& ObjectInitializer);

};

