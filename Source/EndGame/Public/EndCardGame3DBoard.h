#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentSkeletalMeshActor.h"
#include "EndCardGame3DBoard.generated.h"

UCLASS(Blueprintable)
class AEndCardGame3DBoard : public AEndEnvironmentSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Player_Status;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Player_LanePower1;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Player_LanePower2;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Player_LanePower3;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Enemy_Status;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Enemy_LanePower1;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Enemy_LanePower2;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 MPC_Enemy_LanePower3;
    
    AEndCardGame3DBoard(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void DebugTest();
    
};

