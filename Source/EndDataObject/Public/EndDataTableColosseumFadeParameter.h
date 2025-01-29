#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableColosseumFadeParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableColosseumFadeParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 FadeType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FadeTime;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 ObjNameType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 ZOrderType;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Pauseable;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 UserNumber;
    
public:
    ENDDATAOBJECT_API FEndDataTableColosseumFadeParameter();
};

