#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndDialogueGenerateSourceBGFA.generated.h"

class AEndEnvironmentSkeletalMeshActor;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueGenerateSourceBGFA {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BindName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OptionalActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndEnvironmentSkeletalMeshActor> SkeletalMeshClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTemporary;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Condition;
    
    FEndDialogueGenerateSourceBGFA();
};

