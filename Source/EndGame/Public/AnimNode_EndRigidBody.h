#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_RigidBody.h"
#include "AnimNode_EndRigidBody.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndRigidBody : public FAnimNode_RigidBody {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SettingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    FAnimNode_EndRigidBody();
};

