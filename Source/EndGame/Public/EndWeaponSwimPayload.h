#pragma once
#include "CoreMinimal.h"
#include "MovieSceneEndWeaponSwimParameters.h"
#include "EndWeaponSwimPayload.generated.h"

USTRUCT(BlueprintType)
struct FEndWeaponSwimPayload {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RouteName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndWeaponSwimParameters Parameters;
    
    ENDGAME_API FEndWeaponSwimPayload();
};

