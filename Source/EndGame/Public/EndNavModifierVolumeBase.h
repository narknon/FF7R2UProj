#pragma once
#include "CoreMinimal.h"
#include "NavPriorRegistInfo.h"
#include "NavModifierVolume.h"
#include "EndActorBaseInterface.h"
#include "EndNavActorInterface.h"
#include "EndNavModifierVolumeBase.generated.h"

UCLASS(Blueprintable)
class AEndNavModifierVolumeBase : public ANavModifierVolume, public IEndActorBaseInterface, public IEndNavActorInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint64> AffectedPolysCacheRef;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndNavModifierVolumeBase(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

