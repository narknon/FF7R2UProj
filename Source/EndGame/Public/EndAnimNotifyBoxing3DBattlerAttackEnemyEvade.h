#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyBoxing3DBattlerAttackEnemyEvade.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyBoxing3DBattlerAttackEnemyEvade : public UAnimNotify {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform HitTransform;
    
public:
    UEndAnimNotifyBoxing3DBattlerAttackEnemyEvade();

};

