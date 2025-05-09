#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EndWeaponSwimPayload.h"
#include "MovieSceneEndWeaponSwimSectionData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FMovieSceneEndWeaponSwimSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWeaponSwimPayload> KeyValues;
    
public:
    FMovieSceneEndWeaponSwimSectionData();
};

