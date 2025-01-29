#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "EWeaponSlot.h"
#include "EndDialogueConstraintSection.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndDialogueConstraintSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OwnerBindName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ParentBindName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EWeaponSlot Slot;
    
public:
    UEndDialogueConstraintSection();

};

