#pragma once
#include "CoreMinimal.h"
#include "EndChocoboPartsDataSet.h"
#include "EndPlayerCharacter.h"
#include "EndChocoboCharacter.generated.h"

class UEndChocoboAirGlideActionParam;
class UEndChocoboClimbActionParam;
class UEndChocoboCommonActionParam;
class UEndChocoboPartsSkeletalMeshComponent;
class UEndChocoboWaterJetActionParam;

UCLASS(Blueprintable)
class ENDGAME_API AEndChocoboCharacter : public AEndPlayerCharacter {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_Head;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_Body;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_Legs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_EquipHead;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_EquipBody;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndChocoboPartsSkeletalMeshComponent* PartsMeshComp_EquipLegs;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndChocoboCommonActionParam* CommonActionParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndChocoboAirGlideActionParam* AirGlideActionParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndChocoboWaterJetActionParam* WaterJetActionParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndChocoboClimbActionParam* ClimbActionParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboPartsDataSet EquipmentData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DefaultPartsIndex;
    
    AEndChocoboCharacter(const FObjectInitializer& ObjectInitializer);

};

