#include "RebirthDataObjectInspection.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "EndDataObjectBase.h"
#include "EndDataTableRowBase.h"
#include "JsonObjectConverter.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"

namespace
{
    constexpr int32 MaximumRowsToExport = 1000;
    constexpr int32 MaximumRowsToEnumerate = 100000;
    constexpr int32 MaximumRowStructBytes = 1024 * 1024;
    constexpr int32 MaximumArrayElementsPerRow = 16384;

    bool ValidateRowArrayCounts(const UScriptStruct* RowStruct, const uint8* RowData, FString& Error)
    {
        int64 TotalElements = 0;
        for (TFieldIterator<FProperty> It(RowStruct); It; ++It)
        {
            const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(*It);
            if (!ArrayProperty)
            {
                continue;
            }
            const void* ArrayData = ArrayProperty->ContainerPtrToValuePtr<void>(RowData);
            const FScriptArrayHelper Array(ArrayProperty, ArrayData);
            const int32 Count = Array.Num();
            if (Count < 0 || Count > MaximumArrayElementsPerRow)
            {
                Error = FString::Printf(TEXT("Array %s has an invalid or excessive element count: %d"),
                    *ArrayProperty->GetName(), Count);
                return false;
            }
            TotalElements += Count;
            if (TotalElements > MaximumArrayElementsPerRow)
            {
                Error = TEXT("Row exceeds the bounded total array-element budget");
                return false;
            }
        }
        return true;
    }
}

void AppendEndDataObjectDiagnostics(
    UObject* Asset,
    const TSharedRef<FJsonObject>& Diagnostics,
    int32 MaxRows)
{
    if (!IsValid(Asset))
    {
        return;
    }
    const UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Asset);
    if (!DataObject)
    {
        return;
    }

    const TSharedRef<FJsonObject> Result = MakeShared<FJsonObject>();
    Diagnostics->SetObjectField(TEXT("end_data_object"), Result);
    Result->SetStringField(TEXT("inspection_mode"), TEXT("read_only_native_row_map"));
    Result->SetStringField(TEXT("asset_class"), DataObject->GetClass()->GetPathName());
    Result->SetNumberField(TEXT("requested_max_rows"), MaxRows);
    const int32 RowLimit = FMath::Clamp(MaxRows, 0, MaximumRowsToExport);
    Result->SetNumberField(TEXT("effective_max_rows"), RowLimit);

    TArray<TSharedPtr<FJsonValue>> FidelityLimits;
    const TCHAR* Limits[] = {
        TEXT("RowStruct and RowMap are native, unreflected fields; an empty reflected RowStructName does not mean there are no rows."),
        TEXT("This exports the SDK decoder's in-memory values, not a byte-for-byte validation against the retail frozen payload."),
        TEXT("The existing EndDataObject decoder handles only selected scalar and array property types; unsupported or missing fields have no skip/error path and can leave defaults or misalign subsequent decoding."),
        TEXT("The existing decoder reads uint16 in both UInt64 branches; dataobjects using uint64 fields cannot be assumed faithful."),
        TEXT("WorldCondition uses FName, uint8, and arrays of FName, uint8, float and int32, which the decoder handles; exported values still require semantic validation."),
        TEXT("The existing row save/recook path is commented out. This inspection does not establish round-trip save fidelity."),
        TEXT("Rows are bounded; transient/deprecated row properties are omitted by the JSON export. Top-level array element counts are also bounded.")
    };
    for (const TCHAR* Limit : Limits)
    {
        FidelityLimits.Add(MakeShared<FJsonValueString>(Limit));
    }
    Result->SetArrayField(TEXT("fidelity_limits"), FidelityLimits);

    const UEndDataObjectBase::FRowMap& RowMap = DataObject->GetRowMap();
    const int32 RowCount = RowMap.Num();
    Result->SetNumberField(TEXT("row_count"), RowCount);
    if (RowCount < 0 || RowCount > MaximumRowsToEnumerate)
    {
        Result->SetStringField(TEXT("status"), TEXT("row_count_outside_inspection_bounds"));
        return;
    }

    const UScriptStruct* RowStruct = DataObject->GetRowStruct();
    if (!IsValid(RowStruct) || !RowStruct->IsChildOf(FEndDataTableRowBase::StaticStruct()))
    {
        Result->SetStringField(TEXT("status"), TEXT("missing_or_unknown_row_struct"));
        return;
    }
    const int32 StructBytes = RowStruct->GetStructureSize();
    Result->SetStringField(TEXT("row_struct"), RowStruct->GetPathName());
    Result->SetNumberField(TEXT("row_struct_bytes"), StructBytes);
    if (StructBytes <= 0 || StructBytes > MaximumRowStructBytes)
    {
        Result->SetStringField(TEXT("status"), TEXT("row_struct_size_outside_inspection_bounds"));
        return;
    }

    const TArray<FName> RowNames = DataObject->GetRowNames();
    Result->SetNumberField(TEXT("row_name_count"), RowNames.Num());
    Result->SetBoolField(TEXT("row_count_matches_names"), RowNames.Num() == RowCount);
    const int32 CountToInspect = FMath::Min(RowLimit, RowNames.Num());
    Result->SetBoolField(TEXT("rows_truncated"), CountToInspect < RowNames.Num());

    TArray<TSharedPtr<FJsonValue>> NamesJson;
    TArray<TSharedPtr<FJsonValue>> RowsJson;
    int32 ExportedRows = 0;
    for (int32 Index = 0; Index < CountToInspect; ++Index)
    {
        const FName RowName = RowNames[Index];
        NamesJson.Add(MakeShared<FJsonValueString>(RowName.ToString()));
        const TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();
        Row->SetStringField(TEXT("row_name"), RowName.ToString());
        RowsJson.Add(MakeShared<FJsonValueObject>(Row));

        uint8* const* RowPointer = RowMap.Find(RowName);
        if (!RowPointer || !*RowPointer)
        {
            Row->SetStringField(TEXT("status"), TEXT("null_or_missing_row_pointer"));
            continue;
        }
        FString Error;
        if (!ValidateRowArrayCounts(RowStruct, *RowPointer, Error))
        {
            Row->SetStringField(TEXT("status"), TEXT("row_value_count_outside_inspection_bounds"));
            Row->SetStringField(TEXT("error"), Error);
            continue;
        }

        const TSharedRef<FJsonObject> Values = MakeShared<FJsonObject>();
        if (!FJsonObjectConverter::UStructToJsonObject(
            RowStruct, *RowPointer, Values, 0, CPF_Transient | CPF_Deprecated))
        {
            Row->SetStringField(TEXT("status"), TEXT("native_struct_json_export_failed"));
            continue;
        }
        Row->SetObjectField(TEXT("values"), Values);
        Row->SetStringField(TEXT("status"), TEXT("exported"));
        ++ExportedRows;
    }
    Result->SetArrayField(TEXT("row_names"), NamesJson);
    Result->SetArrayField(TEXT("rows"), RowsJson);
    Result->SetNumberField(TEXT("rows_exported"), ExportedRows);
    Result->SetStringField(TEXT("status"), TEXT("inspected_native_rows"));
}
