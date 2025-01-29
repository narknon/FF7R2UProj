#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSequence.h"
#include "EndCameraSequenceObjectPath.h"
#include "EndCameraSequence.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndCameraSequence : public ULevelSequence {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FGuid, FEndCameraSequenceObjectPath> BindingSoftObjectPaths;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FGuid, FString> ObjectPaths;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FGuid, FGuid> ObjectToBindingSoftObjectGuid;
    
public:
    UEndCameraSequence();

};

