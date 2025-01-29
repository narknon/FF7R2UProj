#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Matinee/InterpTrackFloatBase.h"
#include "InterpTrackBonamikCharaWindKey.h"
#include "InterpTrackBonamikCharaWind.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class BONAMIKRT_API UInterpTrackBonamikCharaWind : public UInterpTrackFloatBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, EditFixedSize, meta=(AllowPrivateAccess=true))
    TArray<FInterpTrackBonamikCharaWindKey> m_Keys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector m_DirectionVec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_BaseStrength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_WaveAmplitude;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_WavePeriod;
    
    UInterpTrackBonamikCharaWind();

};

