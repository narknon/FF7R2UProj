#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimNotifyCondorPopSubCharacterPoint.h"
#include "EndAnimNotifyCondorPopSubCharacter.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UEndAnimNotifyCondorPopSubCharacter : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 SubUnitIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimNotifyCondorPopSubCharacterPoint PrimaryPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAnimNotifyCondorPopSubCharacterPoint> SecondaryPoints;
    
    UEndAnimNotifyCondorPopSubCharacter();

};

