#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Volume.h"
#include "EndFieldGridVectorFieldVolume.generated.h"

class UVectorFieldComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndFieldGridVectorFieldVolume : public AVolume {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UVectorFieldComponent* VectorFieldComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_UnitLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FIntVector m_Grid;
    
public:
    AEndFieldGridVectorFieldVolume(const FObjectInitializer& ObjectInitializer);

};

