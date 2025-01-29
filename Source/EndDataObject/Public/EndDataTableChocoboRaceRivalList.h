#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboRaceRivalList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboRaceRivalList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NameID;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 DispName;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Rank;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOffset;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 ChocoboType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 RunType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 EnableKeepPace;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName JockeyCharaSpec;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 HeadPartsIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 HeadColorIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 BodyPartsIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 BodyColorIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 LegPartsIndex;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 LegColorIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboRaceRivalList();
};

