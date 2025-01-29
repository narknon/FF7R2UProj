#pragma once
#include "CoreMinimal.h"
#include "EndPlayParticleActorInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndPlayParticleActorInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 m_Enable: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_SocketName;
    
    ENDGAME_API FEndPlayParticleActorInfo();
};

