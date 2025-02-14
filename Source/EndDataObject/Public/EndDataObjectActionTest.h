#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectBase.h"
#include "EndDataObjectActionTest.generated.h"

class FActionMapped : public TMemoryMappedContent<FMappedContentBase, FMemoryMappedPointerTable>
{
    public:
    FActionMapped();
    virtual ~FActionMapped() override {};
    
};

UCLASS(Blueprintable)
class ENDDATAOBJECT_API UEndDataObjectActionTest : public UEndDataObjectBase {
    GENERATED_BODY()
public:
    UEndDataObjectActionTest();

};

