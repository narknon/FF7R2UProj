#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndNaviMapLayer.h"
#include "EEndNaviMapOpenGroup.h"
#include "EEndNaviMapUniqueIndexOffset.h"
#include "EEndNaviMapVisitGroup.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNaviMapVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NaviMapId;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapLayer LayerNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapOpenGroup OpenGroupNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapVisitGroup VisitGroupNumber;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndNaviMapUniqueIndexOffset UniqueIndexOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CaptureGroup;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreOverlap;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bIgnoreGenetateTexture;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUsedByGridVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector GenerateScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueIndex;
    
    AEndNaviMapVolume(const FObjectInitializer& ObjectInitializer);

};

