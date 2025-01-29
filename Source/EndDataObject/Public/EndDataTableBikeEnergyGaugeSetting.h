#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeEnergyGaugeSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeEnergyGaugeSetting : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnergyGaugeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnergyGaugeDecreeseSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnergyGaugeRecoveryItem;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeEnergyGaugeSetting();
};

