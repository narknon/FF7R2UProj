#include "EndDataObjectPlayerTable.h"

UEndDataObjectPlayerTable::UEndDataObjectPlayerTable() {
	RowStruct = FEndDataTablePlayerTable::StaticStruct();
}

void UEndDataObjectPlayerTable::Serialize(FStructuredArchiveRecord& Record)
{
	Super::Serialize(Record);
}