#include "EndDataObjectBase.h"


#include "EndDataTableRowBase.h"

UEndDataObjectBase::UEndDataObjectBase()
	: UMemoryMappedAsset(FObjectInitializer::Get())
	, RowStruct(nullptr)
{
	
}

void UEndDataObjectBase::AddRowInternal(FName RowName, FEndDataTableRowBase* RowData)
{
	RowMap.Add(RowName, RowData);
}

void UEndDataObjectBase::SaveStructData(FStructuredArchiveSlot Slot)
{
	UScriptStruct* SaveUsingStruct = RowStruct;
	if (!SaveUsingStruct)
	{
		SaveUsingStruct = FEndDataTableRowBase::StaticStruct();
	}

	int32 NumRows = RowMap.Num();
	FStructuredArchiveArray Array = Slot.EnterArray(NumRows);

	// Now iterate over rows in the map
	for (auto RowIt = RowMap.CreateIterator(); RowIt; ++RowIt)
	{
		// Save out name
		FName RowName = RowIt.Key();
		FStructuredArchiveRecord Row = Array.EnterElement().EnterRecord();
		Row << SA_VALUE(TEXT("Name"), RowName);

		// Save out data
		FEndDataTableRowBase* RowData = RowIt.Value();

		SaveUsingStruct->SerializeItem(Row.EnterField(SA_FIELD_NAME(TEXT("Value"))), RowData, nullptr);
	}
}

UScriptStruct& UEndDataObjectBase::GetEmptyUsingStruct() const
{
	UScriptStruct* EmptyUsingStruct = RowStruct;
	if (!EmptyUsingStruct)
	{
		EmptyUsingStruct = FEndDataTableRowBase::StaticStruct();
	}

	return *EmptyUsingStruct;
}

void UEndDataObjectBase::EmptyTable()
{
	UScriptStruct& EmptyUsingStruct = GetEmptyUsingStruct();

	// Iterate over all rows in table and free mem
	for (auto RowIt = RowMap.CreateIterator(); RowIt; ++RowIt)
	{
		FEndDataTableRowBase* RowData = RowIt.Value();
		EmptyUsingStruct.DestroyStruct(RowData);
		FMemory::Free(RowData);
	}

	// Finally empty the map
	RowMap.Empty();
}

void UEndDataObjectBase::LoadStructData(FStructuredArchiveSlot Slot)
{
	UScriptStruct* LoadUsingStruct = RowStruct;
	if (!LoadUsingStruct)
	{
		LoadUsingStruct = FEndDataTableRowBase::StaticStruct();
	}

	int32 NumRows;
	FStructuredArchiveArray Array = Slot.EnterArray(NumRows);
	
	RowMap.Reserve(NumRows);
	for (int32 RowIdx = 0; RowIdx < NumRows; RowIdx++)
	{
		FStructuredArchiveRecord RowRecord = Array.EnterElement().EnterRecord();

		// Load row name
		FName RowName;
		RowRecord << SA_VALUE(TEXT("Name"), RowName);

		// Load row data
		FEndDataTableRowBase* RowData = (FEndDataTableRowBase*)FMemory::Malloc(LoadUsingStruct->GetStructureSize());

		// And be sure to call DestroyScriptStruct later
		LoadUsingStruct->InitializeStruct(RowData);

		LoadUsingStruct->SerializeItem(RowRecord.EnterField(SA_FIELD_NAME(TEXT("Value"))), RowData, nullptr);

		// Add to map
		RowMap.Add(RowName, RowData);
	}
}

void UEndDataObjectBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
}

