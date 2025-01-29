#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndLayoutObjectAppendParameter.h"
#include "EndPackObjectBaseParams.h"
#include "EndLayoutObjectPack.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndLayoutObjectPack : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Category;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndPackObjectBaseParams> Objects;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndLayoutObjectAppendParameter AppendParameters;
    
    AEndLayoutObjectPack(const FObjectInitializer& ObjectInitializer);

};

