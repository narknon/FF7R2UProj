#pragma once
#include "CoreMinimal.h"

#include "EndDataTableRowBase.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableRowBase {
    GENERATED_BODY()
public:
	DECLARE_TYPE_LAYOUT(FEndDataTableRowBase, NonVirtual);

    FEndDataTableRowBase() { }
    virtual ~FEndDataTableRowBase() { }

    /** 
     * Can be overridden by subclasses; Called whenever the owning data table is imported or re-imported.
     * Allows for custom fix-ups, parsing, etc. after initial data is read in.
     * 
     * @param InDataTable					The data table that owns this row
     * @param InRowName						The name of the row we're performing fix-up on
     * @param OutCollectedImportProblems	List of problems accumulated during import; Can be added to via this method
     */
    /*virtual void OnPostDataImport(const UEndDataObjectBase* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) {}

    /**
     * Can be overridden by subclasses; Called on every row when the owning data table is modified
     * Allows for custom fix-ups, parsing, etc for user changes
     * This will be called in addition to OnPostDataImport when importing
     *
     * @param InDataTable					The data table that owns this row
     * @param InRowName						The name of the row we're performing fix-up on
     #1#
    virtual void OnDataObjectChanged(const UEndDataObjectBase* InDataTable, const FName InRowName) {}*/

	friend ENDDATAOBJECT_API FArchive& operator<<(FArchive& Ar, FEndDataTableRowBase& Table);
};

