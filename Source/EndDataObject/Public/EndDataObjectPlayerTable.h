#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectBase.h"
#include "EndDataTablePlayerTable.h"
#include "EndDataObjectPlayerTable.generated.h"

UCLASS(Blueprintable)
class ENDDATAOBJECT_API UEndDataObjectPlayerTable : public UEndDataObjectBase {
    GENERATED_BODY()
public:
    
    UEndDataObjectPlayerTable();

    virtual void Serialize(FStructuredArchiveRecord& Record) override;

};

