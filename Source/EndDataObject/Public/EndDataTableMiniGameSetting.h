#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableMiniGameSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableMiniGameSetting : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 UseSoundLayer;
    
public:
    ENDDATAOBJECT_API FEndDataTableMiniGameSetting();
    
    void Freeze(FMemoryImageWriter& Writer) const
    {
        Writer.WriteObject(UseSoundLayer);
    }
    
};

// Let UE know that this struct has a Freeze method
template<>
struct TStructOpsTypeTraits<FEndDataTableMiniGameSetting>
    : public TStructOpsTypeTraitsBase2<FEndDataTableMiniGameSetting>
{
    enum
    {
        WithFreeze = true,
    };
};