#pragma once
#include "CoreMinimal.h"
#include "MemoryMappedAsset.h"
#include "EndDataObjectBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDDATAOBJECT_API UEndDataObjectBase : public UMemoryMappedAsset {
    GENERATED_BODY()
public:
    UEndDataObjectBase();
    UEndDataObjectBase(const FTypeLayoutDesc& InContentTypeLayout);
    DECLARE_MULTICAST_DELEGATE(FOnDataObjectChanged);
    DECLARE_MULTICAST_DELEGATE(FOnDataObjectImport);
    UScriptStruct*			RowStruct;
    /** Map of name of row to row data structure. */
    TMemoryImageMap<FName, uint8*>		RowMap;

    const FTypeLayoutDesc& ContentTypeLayout{};
    
    /** Called to add rows to the data table */
    virtual void AddRowInternal(FName RowName, uint8* RowDataPtr);

    void SaveStructData(FStructuredArchiveSlot Slot);
    UScriptStruct& GetEmptyUsingStruct() const;
    void EmptyTable();
    void LoadStructData(FStructuredArchiveSlot Slot);
    virtual void Serialize(FArchive& Record);
    
};

