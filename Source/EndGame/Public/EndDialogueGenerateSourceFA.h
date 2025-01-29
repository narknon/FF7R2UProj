#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndDialogueGenerateSourceFA.generated.h"

class AEndSkeletalMeshActor;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueGenerateSourceFA {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BindName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OptionalActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AEndSkeletalMeshActor> SkeletalMeshClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTemporary;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Condition;
    
    FEndDialogueGenerateSourceFA();
};

