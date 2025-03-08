#include "EndDataObjectBase.h"
#include "EndDataTableRowBase.h"

UEndDataObjectBase::UEndDataObjectBase()
	: UMemoryMappedAsset(FObjectInitializer::Get())
	, RowStruct(nullptr)
{
	
}

void UEndDataObjectBase::AddRowInternal(FName RowName, uint8* RowData)
{
	RowMap.Add(RowName, RowData);
}

void UEndDataObjectBase::HandleDataObjectChanged(FName ChangedRowName)
{
	if (IsPendingKillOrUnreachable() || HasAnyFlags(RF_BeginDestroyed))
	{
		// This gets called during destruction, don't broadcast callbacks
		return;
	}
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

TArray<FName> UEndDataObjectBase::GetRowNames() const
{
	TArray<FName> Keys;
	RowMap.GetKeys(Keys);
	return Keys;
}

void UEndDataObjectBase::LoadStructData(FMemoryReader Ar)
{
	// KEYS
	//SparseArray
	PointerTable.ReadPointerData(Ar);
	int64 initialPos = Ar.Tell();

	////////////////TBitArray (allocation flags)
	PointerTable.ReadPointerData(Ar);

	int64 continuePos = Ar.Tell();
	Ar.Seek(initialPos + PointerTable.GetOffsetFromThis(1));

	TArray<int32> Data;
	int32 NumInts = (PointerTable.GetDataSize(1) + 31) / 32;  // Dividing and rounding up
	Data.SetNumUninitialized(NumInts);
	Ar.Serialize(Data.GetData(), NumInts * sizeof(int32));
	Ar.Seek(continuePos);

	TArray<bool> BitData;

	BitData.SetNumUninitialized(PointerTable.GetDataSize(1));

	for (int32 i = 0; i < NumInts; ++i) {
		int32 CurrentInt = Data[i];
		for (int j = 0; j < 32 && (i * 32 + j) < PointerTable.GetDataSize(1); ++j) {
			BitData[i * 32 + j] = (CurrentInt & (1 << j)) != 0;
		}
	}
	/////////////////

	int32 FirstFreeIndex;
	int32 NumFreeIndices;
	Ar << FirstFreeIndex;
	Ar << NumFreeIndices;

	//KEY DATA
	continuePos = Ar.Tell();
	Ar.Seek(PointerTable.GetOffsetFromThis(0));

	TArray<FName> KeyNames;

	for (int i = 0; i < PointerTable.GetDataSize(0); i++)
	{
		int64 start = Ar.Tell();
		if (BitData[i])
		{
			//Name (FMinimalName), Index (int), NextIndex (int), Priority (int)
			uint64 keyHash;
			int32 index;
			int32 nextIndex;
			int32 priority;

			FMinimalName* NamePtr = (FMinimalName*)((uint8*)Content + start);
			FName KeyName = MinimalNameToName(*NamePtr);
			UE_LOG(LogTemp, Warning, TEXT("This is a log message: %s"), *KeyName.ToString());

			KeyNames.Add(KeyName);

			Ar << keyHash; //skip over FMinimalName data
			Ar << index;
			Ar << nextIndex;
			Ar << priority;
		}
		Ar.Seek(start + 20);
	}

	Ar.Seek(continuePos);

	//
	//INDICES

	initialPos = Ar.Tell();
	PointerTable.ReadPointerData(Ar);


	continuePos = Ar.Tell();
	Ar.Seek(initialPos + PointerTable.GetOffsetFromThis(2));

	TArray<int32> Indexes;
	Indexes.SetNumUninitialized(PointerTable.GetDataSize(2));
	Ar.Serialize(Indexes.GetData(), PointerTable.GetDataSize(2) * sizeof(int32));

	Ar.Seek(continuePos);

	//
	//STRUCT DEFINITION

	initialPos = Ar.Tell();
	PointerTable.ReadPointerData(Ar);

	continuePos = Ar.Tell();
	Ar.Seek(initialPos + PointerTable.GetOffsetFromThis(3));

	TArray<FName> PropertyNames;
	for (int i = 0; i < PointerTable.GetDataSize(3); i++)
	{
		//Name (FName), Property (int)
		uint64 NameHash;
		int32 property;

		FMinimalName* NamePtr = (FMinimalName*)((uint8*)Content + Ar.Tell());
		FName PropertyName = MinimalNameToName(*NamePtr);
		//UE_LOG(LogTemp, Warning, TEXT("This is a log message: %s"), *PropertyName.ToString());

		Ar << NameHash; //same here, just skipping
		Ar << property;
		PropertyNames.Add(PropertyName);

	}
	Ar.Seek(continuePos);

	SerializeMember(Ar, KeyNames, PropertyNames);

	FMemory::Free(Content);
	Content = nullptr;
}

void UEndDataObjectBase::SerializeMember(FMemoryReader& Ar, TArray<FName> KeyNames, TArray<FName> PropertyNames)
{
	int64 initialPos = Ar.Tell();
	PointerTable.ReadPointerData(Ar);


	int64 continuePos = Ar.Tell();
	Ar.Seek(initialPos + PointerTable.GetOffsetFromThis(4));

	RowMap.Reserve(PointerTable.GetDataSize(4));
	for (int32 RowIdx = 0; RowIdx < PointerTable.GetDataSize(4); RowIdx++)
	{
		// Load row data
		uint8* RowData = (uint8*)FMemory::Malloc(RowStruct->GetStructureSize());

		// And be sure to call DestroyScriptStruct later
		RowStruct->InitializeStruct(RowData);

		// Iterate over the PropertyNames list (which represents the memory layout)
		for (int32 PropertyIdx = 0; PropertyIdx < PropertyNames.Num(); PropertyIdx++)
		{
			FName CurrentPropertyName = PropertyNames[PropertyIdx];

			// Iterate over the RowStruct properties to find the matching one
			for (TFieldIterator<FProperty> PropIt(RowStruct); PropIt; ++PropIt)
			{
				FProperty* Property = *PropIt;

				// If the current property name matches a property in the struct
				if (Property->GetFName() == CurrentPropertyName)
				{
					void* PropertyPtr = Property->ContainerPtrToValuePtr<void>(RowData);

					// Deserialize data based on the property type
					if (FIntProperty* IntProp = CastField<FIntProperty>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						int32 Value;
						Ar << Value;
						IntProp->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FUInt32Property* UIntProp = CastField<FUInt32Property>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						uint32 Value;
						Ar << Value;
						UIntProp->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						float Value;
						Ar << Value;
						FloatProp->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FInt16Property* Int16Prop = CastField<FInt16Property>(Property))
					{
						int16 Value;
						Ar << Value;
						Int16Prop->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FUInt16Property* UInt16Prop = CastField<FUInt16Property>(Property))
					{
						uint16 Value;
						Ar << Value;
						UInt16Prop->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FInt64Property* Int64Prop = CastField<FInt64Property>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						int64 Value;
						Ar << Value;
						Int64Prop->SetPropertyValue(PropertyPtr, Value);
					}
					else if (FUInt64Property* UInt64Prop = CastField<FUInt64Property>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						uint16 Value;
						Ar << Value;
						UInt64Prop->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Property))
					{
						bool Value;
						Ar << Value;
						BoolProp->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FInt8Property* Int8Prop = CastField<FInt8Property>(Property))
					{
						int8 Value;
						Ar << Value;
						Int8Prop->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FByteProperty* ByteProp = CastField<FByteProperty>(Property))
					{
						uint8 Value;
						Ar << Value;
						ByteProp->SetPropertyValue(PropertyPtr, Value);
					}
					else if (FNameProperty* NameProp = CastField<FNameProperty>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 4));
						FMinimalName* NamePtr = (FMinimalName*)((uint8*)Content + Ar.Tell());
						FName Value = MinimalNameToName(*NamePtr);
						uint64 skip;
						Ar << skip;
						NameProp->SetPropertyValue(PropertyPtr, Value);
					}
					else if (FStrProperty* StringProp = CastField<FStrProperty>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 8));
						initialPos = Ar.Tell();

						uint64 packedArray;
						Ar << packedArray;

						int64 offsetArray = (int64)packedArray >> 1;
						int32 ArrayNum;
						int32 ArrayMax;
						Ar << ArrayNum;
						Ar << ArrayMax;

						continuePos = Ar.Tell();
						Ar.Seek(initialPos + offsetArray);


						TArray<TCHAR> StringData;
						StringData.SetNumUninitialized(ArrayNum + 1); 

						Ar.Serialize(StringData.GetData(), ArrayNum * sizeof(TCHAR));

						StringData[ArrayNum] = 0;

						Ar.Seek(continuePos);

						FString Value;
						Value = FString(StringData.GetData());
						StringProp->SetPropertyValue(PropertyPtr, Value); 
					}
					else if (FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
					{
						Ar.Seek(Align(Ar.Tell(), 8));
						initialPos = Ar.Tell();
						UE_LOG(LogTemp, Warning, TEXT("This is a log message: %lld"), initialPos);

						uint64 packedAr;
						Ar << packedAr;

						int64 offsetArray = (int64)packedAr >> 1;
						int32 NumAr;
						int32 MaxAr;
						Ar << NumAr;
						Ar << MaxAr;

						int align = 4;

						continuePos = Ar.Tell();
						Ar.Seek(initialPos + offsetArray);

						void* ArrayPtr = ArrayProp->ContainerPtrToValuePtr<void>(RowData);

						FScriptArrayHelper ArrayHelper(ArrayProp, ArrayPtr);
						ArrayHelper.Resize(NumAr);  // Make sure the array is resized to fit the expected elements

						for (int32 i = 0; i < NumAr; ++i)
						{
							//void* ElementPtr = ArrayProp->Inner->ContainerPtrToValuePtr<void>(ArrayPtr, i);
							void* ElementPtr = ArrayHelper.GetRawPtr(i);

							// Deserialize the array element based on its type
							if (FIntProperty* ElementIntProp = CastField<FIntProperty>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								int32 ElementValue;
								Ar << ElementValue;
								ElementIntProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FUInt32Property* ElementUIntProp = CastField<FUInt32Property>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								uint32 ElementValue;
								Ar << ElementValue;
								ElementUIntProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FFloatProperty* ElementFloatProp = CastField<FFloatProperty>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								float ElementValue;
								Ar << ElementValue;
								ElementFloatProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FInt16Property* Int16Prop = CastField<FInt16Property>(ArrayProp->Inner))
							{
								align = 2;
								int16 ElementValue;
								Ar << ElementValue;
								Int16Prop->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FUInt16Property* ElementUInt16Prop = CastField<FUInt16Property>(ArrayProp->Inner))
							{
								align = 2;
								uint16 ElementValue;
								Ar << ElementValue;
								ElementUInt16Prop->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FInt64Property* ElementInt64Prop = CastField<FInt64Property>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								int64 ElementValue;
								Ar << ElementValue;
								ElementInt64Prop->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FUInt64Property* ElementUInt64Prop = CastField<FUInt64Property>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								uint16 ElementValue;
								Ar << ElementValue;
								ElementUInt64Prop->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FBoolProperty* ElementBoolProp = CastField<FBoolProperty>(ArrayProp->Inner))
							{
								align = 1;
								bool ElementValue;
								Ar << ElementValue;
								ElementBoolProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FInt8Property* ElementInt8Prop = CastField<FInt8Property>(ArrayProp->Inner))
							{
								align = 1;
								int8 ElementValue;
								Ar << ElementValue;
								ElementInt8Prop->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FByteProperty* ElementByteProp = CastField<FByteProperty>(ArrayProp->Inner))
							{
								align = 1;
								uint8 ElementValue;
								Ar << ElementValue;
								ElementByteProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FNameProperty* ElementNameProp = CastField<FNameProperty>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 4));
								FMinimalName* NamePtr = (FMinimalName*)((uint8*)Content + Ar.Tell());
								FName ElementValue = MinimalNameToName(*NamePtr);
								uint64 skip;
								Ar << skip;
								ElementNameProp->SetPropertyValue(ElementPtr, ElementValue);
							}
							else if (FStrProperty* ElementStringProp = CastField<FStrProperty>(ArrayProp->Inner))
							{
								Ar.Seek(Align(Ar.Tell(), 8));
								initialPos = Ar.Tell();

								uint64 packedString;
								Ar << packedString;

								int64 offsetString = (int64)packedString >> 1;
								int32 CharNum;
								int32 CharMax;
								Ar << CharNum;
								Ar << CharMax;

								long continuePos2 = Ar.Tell();
								Ar.Seek(initialPos + offsetString);

								TArray<TCHAR> StringData;
								StringData.SetNumUninitialized(CharNum + 1);

								Ar.Serialize(StringData.GetData(), CharNum * sizeof(TCHAR));

								Ar.Seek(continuePos2);

								FString Value;
								Value = FString(StringData);
								ElementStringProp->SetPropertyValue(ElementPtr, Value); 
							}
							Ar.Seek(Align(Ar.Tell(), align));
						}

						Ar.Seek(continuePos);
					}

					break; // Break once we find the correct property
				}
			}
		}

		RowMap.Add(KeyNames[RowIdx], RowData);
	}
}

void UEndDataObjectBase::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (!Content || FrozenContentSize == 0)
	{
		return; // No data to process
	}

	if (RowStruct == nullptr)
	{
		return; // RowStruct staticclass not initialized
	}

	// Wrap Content in an FMemoryReader
	TArray<uint8> ContentView(Content, FrozenContentSize);
	FMemoryReader MemoryReader(ContentView, true); // true = treat it as persistent

	if (Ar.IsSaving())
	{
		//SaveStructData(Slot);
	}
	else if (Ar.IsLoading())
	{
		EmptyTable();
		LoadStructData(MemoryReader);
	}

	return;

}

#if WITH_EDITORONLY_DATA
FName UEndDataObjectBase::GetRowStructName() const
{
	return (RowStruct) ? RowStruct->GetFName() : RowStructName;
}
#endif //WITH_EDITORONLY_DATA