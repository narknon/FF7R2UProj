#pragma once
#include "CoreMinimal.h"
#include "EndMassiveEnvironmentRenderData.h"
#include "EndMassiveEnvironmentComponent.generated.h"

USTRUCT(BlueprintType)
struct FEndMassiveEnvironmentComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndMassiveEnvironmentRenderData> RenderData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 AssetPathIndex;
    
    ENDGAME_API FEndMassiveEnvironmentComponent();
};

