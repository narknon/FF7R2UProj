#include "EndDataObjectBase.h"

#include "EndDataTableMiniGameSetting.h"
#include "EndDataTableRowBase.h"

UEndDataObjectBase::UEndDataObjectBase()
	: RowStruct(nullptr)
{}

UEndDataObjectBase::UEndDataObjectBase(const FTypeLayoutDesc& InContentTypeLayout)
	: ContentTypeLayout(InContentTypeLayout)
	, RowStruct(nullptr)
{}

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

void UEndDataObjectBase::Serialize(FArchive& Ar)
{
	if(Ar.IsSaving())
	{
		// Suppose we have an instance of the struct:
		FEndDataTableMiniGameSetting MyData;

		// Create the memory image container
		FMemoryImage MemoryImage;

		// Create a writer that will fill that image
		FMemoryImageWriter Writer(MemoryImage);

		// "Freeze" (serialize) our struct into MemoryImage
		MyData.Freeze(Writer);

		FMemoryImageResult MemoryImageResult;
		MemoryImage.Flatten(MemoryImageResult, true);

		MemoryImageResult.SaveToArchive(Ar);
	}
	else if(Ar.IsLoading())
	{
		uint32 FrozenContentSize;
		Ar << FrozenContentSize;
		// ensure frozen content is at least as big as our FShaderMapContent-derived class
		checkf(FrozenContentSize >= ContentTypeLayout.Size, TEXT("Invalid FrozenContentSize for %s, got %d, expected at least %d"), ContentTypeLayout.Name, FrozenContentSize, ContentTypeLayout.Size);

		void* ContentMemory = FMemory::Malloc(FrozenContentSize);
		Ar.Serialize(ContentMemory, FrozenContentSize);
		
		FMemoryImageResult::ApplyPatchesFromArchive(ContentMemory, Ar);
	}
}

