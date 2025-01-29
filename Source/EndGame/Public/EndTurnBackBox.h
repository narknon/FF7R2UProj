#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndTurnBackBox.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndTurnBackBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndTriggerBox* m_pTurnBackTriggerBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndTriggerBox* m_pFollowDiscardTriggerBox;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UBoxComponent* m_pBlockWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnableBlockWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOverwriteResetPitch;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverwriteResetPitch;
    
public:
    AEndTurnBackBox(const FObjectInitializer& ObjectInitializer);

};

