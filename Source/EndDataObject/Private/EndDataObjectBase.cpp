#include "EndDataObjectBase.h"

#include "EndDataTableRowBase.h"

UEndDataObjectBase::UEndDataObjectBase() {
	RowStruct = nullptr;
}

void UEndDataObjectBase::AddRowInternal(FName RowName, uint8* RowData)
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
		uint8* RowData = RowIt.Value();

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
		uint8* RowData = RowIt.Value();
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
		uint8* RowData = (uint8*)FMemory::Malloc(LoadUsingStruct->GetStructureSize());

		// And be sure to call DestroyScriptStruct later
		LoadUsingStruct->InitializeStruct(RowData);

		LoadUsingStruct->SerializeItem(RowRecord.EnterField(SA_FIELD_NAME(TEXT("Value"))), RowData, nullptr);

		// Add to map
		RowMap.Add(RowName, RowData);
	}
}

void UEndDataObjectBase::Serialize(FStructuredArchiveRecord& Record)
{
	FArchive& BaseArchive = Record.GetUnderlyingArchive();
	
	Super::Serialize(Record); // When loading, this should load our RowStruct!	

	if (RowStruct && RowStruct->HasAnyFlags(RF_NeedLoad))
	{
		auto RowStructLinker = RowStruct->GetLinker();
		if (RowStructLinker)
		{
			RowStructLinker->Preload(RowStruct);
		}
	}

	if(BaseArchive.IsLoading())
	{
		EmptyTable();
		LoadStructData(Record.EnterField(SA_FIELD_NAME(TEXT("Data"))));
	}
	else if(BaseArchive.IsSaving())
	{
		SaveStructData(Record.EnterField(SA_FIELD_NAME(TEXT("Data"))));
	}
}

