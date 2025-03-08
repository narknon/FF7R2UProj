#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "MemoryMappedAsset.h"
#include "EndDataObjectBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDDATAOBJECT_API UEndDataObjectBase : public UMemoryMappedAsset {
    GENERATED_BODY()
public:
    using FRowMap = TMemoryImageMap<FName, uint8*>;
    UEndDataObjectBase();

    DECLARE_MULTICAST_DELEGATE(FOnDataObjectChanged);
    DECLARE_MULTICAST_DELEGATE(FOnDataObjectImport);
    UScriptStruct*			RowStruct;
//protected:
    /** Map of name of row to row data structure. */
    FRowMap                 RowMap;

    // TODO: remove this, it is temporarily here to allow DataObjectEditorUtils to compile until I get around to updating functions like RemoveRow and RenameRow
    virtual FRowMap& GetNonConstRowMap() { return RowMap; }

    /** Called to add rows to the data object */
    virtual void AddRowInternal(FName RowName, uint8* RowData);

    virtual long Align(long ptr, int alignment)
    {
        return (ptr + alignment - 1) & ~(alignment - 1);
    }
public:
    virtual const FRowMap& GetRowMap() const { return RowMap; }
    virtual const FRowMap& GetRowMap() { return RowMap; }

    const UScriptStruct* GetRowStruct() const { return RowStruct; }

    UScriptStruct& GetEmptyUsingStruct() const;


    uint8* FindRowUnchecked(FName RowName, bool MustExist = false) const
    {
        if (RowStruct == nullptr)
        {
            //UE_CLOG(MustExist, LogDataObject, Error, TEXT("UDataTable::FindRowUnchecked : DataObject '%s' has no RowStruct specified (%s)."), *GetPathName(), *ContextString);
            return nullptr;
        }

        if (RowName == NAME_None)
        {
            //UE_CLOG(MustExist, LogDataObject, Warning, TEXT("UDataTable::FindRowUnchecked : NAME_None is invalid row name for DataObject '%s' (%s)."), *GetPathName(), *ContextString);
            return nullptr;
        }

        uint8* const* RowDataPtr = GetRowMap().Find(RowName);

        if (RowDataPtr == nullptr)
        {
            return nullptr;
        }

        uint8* RowData = *RowDataPtr;
        check(RowData);

        return RowData;
    }

    void EmptyTable();

    void SerializeMember(FMemoryReader& MemoryReader, TArray<FName> KeyNames, TArray<FName> PropertyNames);

    virtual void Serialize(FArchive& Record);

    TArray<FName> GetRowNames() const;	

    /**
     * Call whenever the data of a object has changed, this calls the OnDataObjectChanged() delegate and per-row callbacks.
     * If ChangedRowName is not none, only that row was changed, otherwise assume all rows have changed
     */
    void HandleDataObjectChanged(FName ChangedRowName = NAME_None);

#if WITH_EDITORONLY_DATA
    FName GetRowStructName() const;


    /** The name of the RowStruct we were using when we were last saved */
    UPROPERTY()
    FName RowStructName;

#endif	// WITH_EDITORONLY_DATA

protected:
    void SaveStructData(FStructuredArchiveSlot Slot);
    void LoadStructData(FMemoryReader MemoryReader);
    
};

