#include "RebirthDataObjectFormat.h"

#include "Containers/BitArray.h"
#include "Hash/CityHash.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/CString.h"
#include "UObject/Class.h"
#include "UObject/EnumProperty.h"
#include "UObject/UnrealType.h"

namespace RebirthDataObjectFormat
{
namespace
{
	constexpr int64 RootSize = 88;
	constexpr int64 KeyElementSize = 20;
	constexpr int64 FieldEntrySize = 12;

	bool IsPodType(int32 Code)
	{
		return Code >= TypeBool && Code <= TypeFloat;
	}

	int32 PodSize(int32 Code)
	{
		switch (Code)
		{
		case TypeBool:
		case TypeUInt8:
		case TypeInt8:
			return 1;
		case TypeUInt16:
		case TypeInt16:
			return 2;
		case TypeUInt32:
		case TypeInt32:
		case TypeFloat:
			return 4;
		case TypeInt64:
			return 8;
		default:
			return 0;
		}
	}

	int32 ElementSize(int32 Code)
	{
		return Code == TypeString ? 16 : (Code == TypeName ? 8 : PodSize(Code));
	}

	int32 ElementAlignment(int32 Code)
	{
		return Code == TypeString ? 8 : (Code == TypeName ? 4 : PodSize(Code));
	}

	int64 AlignUp(int64 Value, int64 Alignment)
	{
		return (Value + Alignment - 1) & ~(Alignment - 1);
	}

	bool IsCompatible(const FProperty* Property, int32 Code)
	{
		if (Property->ArrayDim != 1)
		{
			return false;
		}
		if (Code == TypeString)
		{
			return Property->IsA<FStrProperty>();
		}
		if (Code == TypeName)
		{
			return Property->IsA<FNameProperty>();
		}
		if (!IsPodType(Code) || Property->ElementSize != PodSize(Code))
		{
			return false;
		}
		if (Code == TypeFloat)
		{
			return Property->IsA<FFloatProperty>();
		}
		if (const FBoolProperty* Bool = CastField<FBoolProperty>(Property))
		{
			return Bool->IsNativeBool();
		}
		if (Property->IsA<FFloatProperty>() || Property->IsA<FDoubleProperty>())
		{
			return false;
		}
		// Integers of the same size are stored bit for bit, whatever their signedness in this project.
		return Property->IsA<FNumericProperty>() || Property->IsA<FEnumProperty>();
	}

	struct FReader
	{
		const uint8* Data = nullptr;
		int64 Size = 0;

		bool Has(int64 Offset, int64 Bytes) const
		{
			return Offset >= 0 && Bytes >= 0 && Offset <= Size && Bytes <= Size - Offset;
		}

		int32 I32(int64 Offset) const
		{
			int32 Value;
			FMemory::Memcpy(&Value, Data + Offset, sizeof(Value));
			return Value;
		}

		int64 I64(int64 Offset) const
		{
			int64 Value;
			FMemory::Memcpy(&Value, Data + Offset, sizeof(Value));
			return Value;
		}

		/** A frozen array or string {pointer, num, max} at Offset; OutData is INDEX_NONE for an empty one. */
		bool Array(int64 Offset, int64& OutData, int32& OutNum, FString& OutError) const
		{
			if (!Has(Offset, 16))
			{
				OutError = FString::Printf(TEXT("array header at offset %lld is outside the data"), Offset);
				return false;
			}
			const int64 Packed = I64(Offset);
			OutNum = I32(Offset + 8);
			const int32 Max = I32(Offset + 12);
			if (OutNum < 0 || Max < OutNum)
			{
				OutError = FString::Printf(TEXT("array at offset %lld has an invalid size (%d of %d)"), Offset, OutNum, Max);
				return false;
			}
			if (OutNum == 0)
			{
				OutData = INDEX_NONE;
				return true;
			}
			if ((Packed & 1) == 0)
			{
				OutError = FString::Printf(TEXT("array at offset %lld does not point into the data"), Offset);
				return false;
			}
			OutData = Offset + (Packed >> 1);
			return true;
		}
	};

	bool ReadValue(const FReader& Reader, int64 At, int32 Code, void* Value, FNameAt NameAt, FString& OutError)
	{
		if (Code == TypeString)
		{
			int64 CharsAt = INDEX_NONE;
			int32 Num = 0;
			if (!Reader.Array(At, CharsAt, Num, OutError))
			{
				return false;
			}
			FString& String = *static_cast<FString*>(Value);
			if (Num == 0)
			{
				String.Empty();
				return true;
			}
			if (!Reader.Has(CharsAt, int64(Num) * 2))
			{
				OutError = FString::Printf(TEXT("string at offset %lld is outside the data"), At);
				return false;
			}
			TArray<TCHAR>& Chars = String.GetCharArray();
			Chars.SetNumUninitialized(Num);
			for (int32 Index = 0; Index < Num; ++Index)
			{
				uint16 Unit;
				FMemory::Memcpy(&Unit, Reader.Data + CharsAt + int64(Index) * 2, sizeof(Unit));
				Chars[Index] = static_cast<TCHAR>(Unit);
			}
			if (Chars.Last() != 0)
			{
				Chars.Add(0);
			}
			return true;
		}
		if (Code == TypeName)
		{
			if (!Reader.Has(At, 8))
			{
				OutError = FString::Printf(TEXT("name at offset %lld is outside the data"), At);
				return false;
			}
			*static_cast<FName*>(Value) = NameAt(uint32(At));
			return true;
		}
		const int32 Size = PodSize(Code);
		if (!Reader.Has(At, Size))
		{
			OutError = FString::Printf(TEXT("value at offset %lld is outside the data"), At);
			return false;
		}
		FMemory::Memcpy(Value, Reader.Data + At, Size);
		return true;
	}

	bool ReadField(const FReader& Reader, int64 At, const FField& Field, uint8* Row, FNameAt NameAt, FString& OutError)
	{
		void* Value = Field.Property->ContainerPtrToValuePtr<void>(Row);
		if (!Field.bArray)
		{
			return ReadValue(Reader, At, Field.TypeCode, Value, NameAt, OutError);
		}
		int64 ElementsAt = INDEX_NONE;
		int32 Num = 0;
		if (!Reader.Array(At, ElementsAt, Num, OutError))
		{
			return false;
		}
		const int32 Stride = ElementSize(Field.TypeCode);
		if (Num > 0 && !Reader.Has(ElementsAt, int64(Num) * Stride))
		{
			OutError = FString::Printf(TEXT("array elements at offset %lld are outside the data"), ElementsAt);
			return false;
		}
		FScriptArrayHelper Helper(CastFieldChecked<FArrayProperty>(Field.Property), Value);
		Helper.EmptyAndAddValues(Num);
		for (int32 Index = 0; Index < Num; ++Index)
		{
			if (!ReadValue(Reader, ElementsAt + int64(Index) * Stride, Field.TypeCode, Helper.GetRawPtr(Index), NameAt, OutError))
			{
				return false;
			}
		}
		return true;
	}

	bool NameLess(const FName& A, const FName& B)
	{
		const int32 Compare = A.GetPlainNameString().Compare(B.GetPlainNameString(), ESearchCase::IgnoreCase);
		return Compare != 0 ? Compare < 0 : A.GetNumber() < B.GetNumber();
	}

	struct FSection
	{
		TArray<uint8> Data;
		int32 Alignment = 1;
		TArray<TPair<int32, int32>> Pointers; // offset in this section, target section
		TArray<TPair<int32, FName>> Names;    // offset in this section, name
	};

	/** Mirrors the engine's memory image writer: one section per allocation, created in depth-first order. */
	class FImageWriter
	{
	public:
		int32 NewSection(int32 InAlignment)
		{
			const int32 NewIndex = Sections.AddDefaulted();
			Sections[NewIndex].Alignment = InAlignment;
			return NewIndex;
		}

		void Append(int32 Section, const void* Source, int32 Num)
		{
			Sections[Section].Data.Append(static_cast<const uint8*>(Source), Num);
		}

		void AppendZeros(int32 Section, int32 Num)
		{
			Sections[Section].Data.AddZeroed(Num);
		}

		void AppendInt32(int32 Section, int32 InValue)
		{
			Append(Section, &InValue, sizeof(InValue));
		}

		void AppendPointer(int32 Section, int32 Target)
		{
			Sections[Section].Pointers.Emplace(Sections[Section].Data.Num(), Target);
			AppendZeros(Section, 8);
		}

		void AppendName(int32 Section, FName InName)
		{
			if (!InName.IsNone())
			{
				Sections[Section].Names.Emplace(Sections[Section].Data.Num(), InName);
			}
			AppendZeros(Section, 8);
		}

		int32 SectionSize(int32 Section) const
		{
			return Sections[Section].Data.Num();
		}

		void PadSectionTo(int32 Section, int32 TargetSize)
		{
			const int32 Missing = TargetSize - Sections[Section].Data.Num();
			if (Missing > 0)
			{
				AppendZeros(Section, Missing);
			}
		}

		void AppendValue(int32 Section, int32 Code, const void* Source)
		{
			if (Code == TypeString)
			{
				const FString& String = *static_cast<const FString*>(Source);
				const int32 Len = String.Len();
				if (Len == 0)
				{
					AppendZeros(Section, 16);
					return;
				}
				const int32 Chars = NewSection(2);
				const TCHAR* Text = *String;
				for (int32 CharIndex = 0; CharIndex <= Len; ++CharIndex)
				{
					const uint16 Unit = CharIndex < Len ? static_cast<uint16>(Text[CharIndex]) : 0;
					Append(Chars, &Unit, sizeof(Unit));
				}
				AppendPointer(Section, Chars);
				AppendInt32(Section, Len + 1);
				AppendInt32(Section, Len + 1);
				return;
			}
			if (Code == TypeName)
			{
				AppendName(Section, *static_cast<const FName*>(Source));
				return;
			}
			Append(Section, Source, PodSize(Code));
		}

		void AppendField(int32 Section, const FField& InField, const uint8* Row)
		{
			const void* Source = InField.Property->ContainerPtrToValuePtr<void>(Row);
			if (!InField.bArray)
			{
				AppendValue(Section, InField.TypeCode, Source);
				return;
			}
			FScriptArrayHelper Helper(CastFieldChecked<FArrayProperty>(InField.Property), Source);
			const int32 Num = Helper.Num();
			if (Num == 0)
			{
				AppendZeros(Section, 16);
				return;
			}
			const int32 Elements = NewSection(ElementAlignment(InField.TypeCode));
			AppendPointer(Section, Elements);
			AppendInt32(Section, Num);
			AppendInt32(Section, Num);
			for (int32 ElementIndex = 0; ElementIndex < Num; ++ElementIndex)
			{
				AppendValue(Elements, InField.TypeCode, Helper.GetRawPtr(ElementIndex));
			}
		}

		/** Lays the sections out in creation order, storing identical pointer-free sections once, and resolves pointers. */
		void Flatten(FImage& Out) const
		{
			const int32 NumSections = Sections.Num();
			TArray<int32> Canonical;
			Canonical.SetNumUninitialized(NumSections);
			TArray<int64> Offsets;
			Offsets.Init(INDEX_NONE, NumSections);
			TMultiMap<uint64, int32> Unique;
			TArray<uint8>& Content = Out.Content;
			Content.Reset();
			for (int32 SectionIndex = 0; SectionIndex < NumSections; ++SectionIndex)
			{
				const FSection& Section = Sections[SectionIndex];
				if (Section.Pointers.Num() == 0)
				{
					const uint64 Key = SectionKey(Section);
					int32 Found = INDEX_NONE;
					for (TMultiMap<uint64, int32>::TConstKeyIterator It(Unique, Key); It; ++It)
					{
						if (SameSection(Sections[It.Value()], Section))
						{
							Found = It.Value();
							break;
						}
					}
					if (Found != INDEX_NONE)
					{
						Canonical[SectionIndex] = Found;
						continue;
					}
					Unique.Add(Key, SectionIndex);
				}
				Canonical[SectionIndex] = SectionIndex;
				const int64 Offset = AlignUp(Content.Num(), Section.Alignment);
				Content.AddZeroed(int32(Offset - Content.Num()));
				Offsets[SectionIndex] = Offset;
				Content.Append(Section.Data);
			}
			Content.AddZeroed(int32(AlignUp(Content.Num(), 16) - Content.Num()));

			TMap<FName, TArray<uint32>> NameOffsets;
			for (int32 SectionIndex = 0; SectionIndex < NumSections; ++SectionIndex)
			{
				if (Canonical[SectionIndex] != SectionIndex)
				{
					continue;
				}
				const FSection& Section = Sections[SectionIndex];
				for (const TPair<int32, int32>& SectionPointer : Section.Pointers)
				{
					const int64 Location = Offsets[SectionIndex] + SectionPointer.Key;
					const int64 Target = Offsets[Canonical[SectionPointer.Value]];
					const int64 Packed = int64(uint64(Target - Location) << 1) | 1;
					FMemory::Memcpy(Content.GetData() + Location, &Packed, sizeof(Packed));
				}
				for (const TPair<int32, FName>& SectionName : Section.Names)
				{
					NameOffsets.FindOrAdd(SectionName.Value).Add(uint32(Offsets[SectionIndex] + SectionName.Key));
				}
			}
			NameOffsets.KeySort([](const FName& A, const FName& B) { return NameLess(A, B); });
			Out.Names.Reset(NameOffsets.Num());
			for (TPair<FName, TArray<uint32>>& Pair : NameOffsets)
			{
				Pair.Value.Sort();
				Out.Names.Emplace(Pair.Key, MoveTemp(Pair.Value));
			}
		}

	private:
		static uint64 SectionKey(const FSection& Section)
		{
			uint64 Key = CityHash64(reinterpret_cast<const char*>(Section.Data.GetData()), uint32(Section.Data.Num()));
			for (const TPair<int32, FName>& SectionName : Section.Names)
			{
				Key = Key * 0x9E3779B97F4A7C15ull + (uint64(uint32(SectionName.Key)) << 32 | uint64(GetTypeHash(SectionName.Value)));
			}
			return Key;
		}

		static bool SameSection(const FSection& A, const FSection& B)
		{
			if (A.Data != B.Data || A.Names.Num() != B.Names.Num())
			{
				return false;
			}
			for (int32 NameIndex = 0; NameIndex < A.Names.Num(); ++NameIndex)
			{
				if (A.Names[NameIndex].Key != B.Names[NameIndex].Key || A.Names[NameIndex].Value != B.Names[NameIndex].Value)
				{
					return false;
				}
			}
			return true;
		}

		TArray<FSection> Sections;
	};
}

const TCHAR* TypeCodeName(int32 TypeCode)
{
	switch (TypeCode)
	{
	case TypeBool: return TEXT("bool");
	case TypeUInt8: return TEXT("uint8");
	case TypeInt8: return TEXT("int8");
	case TypeUInt16: return TEXT("uint16");
	case TypeInt16: return TEXT("int16");
	case TypeUInt32: return TEXT("uint32");
	case TypeInt32: return TEXT("int32");
	case TypeInt64: return TEXT("int64");
	case TypeFloat: return TEXT("float");
	case TypeString: return TEXT("FString");
	case TypeName: return TEXT("FName");
	default: return TEXT("unknown type");
	}
}

bool FLayout::Build(const UScriptStruct* RowStruct, const TArray<FName>& FieldNames, const TArray<int32>& FieldTypes, FString& OutError)
{
	Fields.Reset();
	RowSize = 0;
	RowAlignment = 1;
	if (!RowStruct)
	{
		OutError = TEXT("there is no row struct");
		return false;
	}
	if (FieldNames.Num() != FieldTypes.Num() || FieldNames.Num() == 0)
	{
		OutError = TEXT("the game's row layout is missing");
		return false;
	}
	int64 Offset = 0;
	TSet<FName> Seen;
	for (int32 Index = 0; Index < FieldNames.Num(); ++Index)
	{
		FField Field;
		Field.Name = FieldNames[Index];
		Field.TypeCode = FieldTypes[Index];
		if (Field.Name.IsNone() || Seen.Contains(Field.Name))
		{
			OutError = FString::Printf(TEXT("the game's row layout has an invalid field name at position %d"), Index);
			return false;
		}
		Seen.Add(Field.Name);
		if (!IsPodType(Field.TypeCode) && Field.TypeCode != TypeString && Field.TypeCode != TypeName)
		{
			OutError = FString::Printf(TEXT("field %s has type code %d, which is not supported"), *Field.Name.ToString(), Field.TypeCode);
			return false;
		}
		Field.Property = FindFProperty<FProperty>(RowStruct, Field.Name);
		if (!Field.Property)
		{
			OutError = FString::Printf(TEXT("the game's rows have a field %s that %s in this project does not have"), *Field.Name.ToString(), *RowStruct->GetName());
			return false;
		}
		const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Field.Property);
		Field.bArray = ArrayProperty != nullptr;
		Field.ValueProperty = ArrayProperty ? ArrayProperty->Inner : Field.Property;
		if (!Field.ValueProperty || !IsCompatible(Field.ValueProperty, Field.TypeCode))
		{
			OutError = FString::Printf(TEXT("field %s is %s in %s but holds %s in the game"), *Field.Name.ToString(), *Field.Property->GetCPPType(),
				*RowStruct->GetName(), TypeCodeName(Field.TypeCode));
			return false;
		}
		const int32 Size = Field.bArray ? 16 : ElementSize(Field.TypeCode);
		const int32 Alignment = Field.bArray ? 8 : ElementAlignment(Field.TypeCode);
		Offset = AlignUp(Offset, Alignment);
		Field.Offset = int32(Offset);
		Offset += Size;
		RowAlignment = FMath::Max(RowAlignment, Alignment);
		Fields.Add(Field);
	}
	RowSize = int32(AlignUp(Offset, RowAlignment));
	return true;
}

uint32 HashRowName(FName Name)
{
	const FString Plain = Name.GetPlainNameString();
	uint64 Hash = 0;
	if (FCString::IsPureAnsi(*Plain))
	{
		TArray<ANSICHAR> Lower;
		Lower.SetNumUninitialized(Plain.Len());
		for (int32 Index = 0; Index < Plain.Len(); ++Index)
		{
			const TCHAR Char = Plain[Index];
			Lower[Index] = static_cast<ANSICHAR>(Char >= TEXT('A') && Char <= TEXT('Z') ? Char + (TEXT('a') - TEXT('A')) : Char);
		}
		Hash = CityHash64(Lower.GetData(), uint32(Lower.Num()));
	}
	else
	{
		TArray<uint16> Lower;
		Lower.SetNumUninitialized(Plain.Len());
		for (int32 Index = 0; Index < Plain.Len(); ++Index)
		{
			Lower[Index] = static_cast<uint16>(FChar::ToLower(Plain[Index]));
		}
		Hash = CityHash64(reinterpret_cast<const char*>(Lower.GetData()), uint32(Lower.Num() * sizeof(uint16)));
	}
	return uint32(Hash) + uint32(Name.GetNumber());
}

int32 HashBucketCount(int32 NumRows)
{
	if (NumRows >= 4)
	{
		return int32(FMath::RoundUpToPowerOfTwo(uint32(NumRows / 2 + 8)));
	}
	return NumRows > 0 ? 1 : 0;
}

void FreeRows(const UScriptStruct* RowStruct, TArray<uint8*>& Rows)
{
	for (uint8* Row : Rows)
	{
		if (Row)
		{
			if (RowStruct)
			{
				RowStruct->DestroyStruct(Row);
			}
			FMemory::Free(Row);
		}
	}
	Rows.Reset();
}

bool Decode(const uint8* Content, int64 ContentSize, FNameAt NameAt, const UScriptStruct* RowStruct, FDecoded& Out, FString& OutError)
{
	FreeRows(RowStruct, Out.Rows);
	Out = FDecoded();
	if (!RowStruct)
	{
		OutError = TEXT("the data object class has no row struct");
		return false;
	}
	const FReader Reader{ Content, ContentSize };
	if (!Content || !Reader.Has(0, RootSize))
	{
		OutError = TEXT("the data is too small for a data object");
		return false;
	}
	int64 KeysAt = INDEX_NONE;
	int32 NumKeys = 0;
	int64 FieldsAt = INDEX_NONE;
	int32 NumFields = 0;
	int64 RowsAt = INDEX_NONE;
	int32 NumRows = 0;
	if (!Reader.Array(0, KeysAt, NumKeys, OutError) || !Reader.Array(56, FieldsAt, NumFields, OutError) || !Reader.Array(72, RowsAt, NumRows, OutError))
	{
		return false;
	}
	if (NumKeys != NumRows)
	{
		OutError = FString::Printf(TEXT("the data has %d row names but %d rows"), NumKeys, NumRows);
		return false;
	}
	if ((NumKeys > 0 && !Reader.Has(KeysAt, NumKeys * KeyElementSize)) || (NumFields > 0 && !Reader.Has(FieldsAt, NumFields * FieldEntrySize)))
	{
		OutError = TEXT("the row names or the row layout are outside the data");
		return false;
	}

	for (int32 Index = 0; Index < NumFields; ++Index)
	{
		const int64 At = FieldsAt + Index * FieldEntrySize;
		Out.FieldNames.Add(NameAt(uint32(At)));
		Out.FieldTypes.Add(Reader.I32(At + 8));
	}
	FLayout Layout;
	if (!Layout.Build(RowStruct, Out.FieldNames, Out.FieldTypes, OutError))
	{
		return false;
	}
	if (NumRows > 0 && !Reader.Has(RowsAt, int64(NumRows) * Layout.RowSize))
	{
		OutError = FString::Printf(TEXT("%d rows of %d bytes do not fit in the data"), NumRows, Layout.RowSize);
		return false;
	}

	// The row map's value is the row index.
	Out.RowNames.Init(NAME_None, NumRows);
	TBitArray<> Seen(false, NumRows);
	for (int32 Index = 0; Index < NumKeys; ++Index)
	{
		const int64 At = KeysAt + Index * KeyElementSize;
		const int32 RowIndex = Reader.I32(At + 8);
		const FName RowName = NameAt(uint32(At));
		if (RowIndex < 0 || RowIndex >= NumRows || Seen[RowIndex] || RowName.IsNone())
		{
			OutError = FString::Printf(TEXT("row name %d is invalid"), Index);
			return false;
		}
		Seen[RowIndex] = true;
		Out.RowNames[RowIndex] = RowName;
	}

	Out.Rows.Reserve(NumRows);
	for (int32 RowIndex = 0; RowIndex < NumRows; ++RowIndex)
	{
		uint8* Row = static_cast<uint8*>(FMemory::Malloc(RowStruct->GetStructureSize()));
		RowStruct->InitializeStruct(Row);
		Out.Rows.Add(Row);
		const int64 Base = RowsAt + int64(RowIndex) * Layout.RowSize;
		for (const FField& Field : Layout.Fields)
		{
			FString FieldError;
			if (!ReadField(Reader, Base + Field.Offset, Field, Row, NameAt, FieldError))
			{
				OutError = FString::Printf(TEXT("row %s, field %s: %s"), *Out.RowNames[RowIndex].ToString(), *Field.Name.ToString(), *FieldError);
				FreeRows(RowStruct, Out.Rows);
				return false;
			}
		}
	}
	return true;
}

bool Encode(const FLayout& Layout, const TArray<FName>& RowNames, const TArray<const uint8*>& Rows, FImage& Out, FString& OutError)
{
	Out = FImage();
	if (RowNames.Num() != Rows.Num())
	{
		OutError = TEXT("row names and rows do not match");
		return false;
	}
	const int32 NumRows = Rows.Num();
	if (NumRows > 0 && Layout.Fields.Num() == 0)
	{
		OutError = TEXT("the row layout is empty");
		return false;
	}
	FImageWriter Writer;
	const int32 Root = Writer.NewSection(8);

	// Row map: TSet elements {name, row index, next in bucket, bucket}, allocation bits, then the bucket heads.
	if (NumRows > 0)
	{
		const int32 HashSize = HashBucketCount(NumRows);
		TArray<int32> Buckets;
		Buckets.Init(INDEX_NONE, HashSize);
		TArray<int32> Next;
		Next.SetNumUninitialized(NumRows);
		TArray<int32> Bucket;
		Bucket.SetNumUninitialized(NumRows);
		for (int32 Index = 0; Index < NumRows; ++Index)
		{
			if (RowNames[Index].IsNone() || !Rows[Index])
			{
				OutError = FString::Printf(TEXT("row %d has no name or no data"), Index);
				return false;
			}
			const int32 HashIndex = int32(HashRowName(RowNames[Index]) & uint32(HashSize - 1));
			Bucket[Index] = HashIndex;
			Next[Index] = Buckets[HashIndex];
			Buckets[HashIndex] = Index;
		}
		const int32 Keys = Writer.NewSection(4);
		for (int32 Index = 0; Index < NumRows; ++Index)
		{
			Writer.AppendName(Keys, RowNames[Index]);
			Writer.AppendInt32(Keys, Index);
			Writer.AppendInt32(Keys, Next[Index]);
			Writer.AppendInt32(Keys, Bucket[Index]);
		}
		Writer.AppendPointer(Root, Keys);
		Writer.AppendInt32(Root, NumRows);
		Writer.AppendInt32(Root, NumRows);

		const int32 Bits = Writer.NewSection(4);
		for (int32 Word = 0; Word < (NumRows + 31) / 32; ++Word)
		{
			const int32 Count = FMath::Min(32, NumRows - Word * 32);
			const uint32 Value = Count == 32 ? 0xFFFFFFFFu : ((1u << Count) - 1u);
			Writer.Append(Bits, &Value, sizeof(Value));
		}
		Writer.AppendPointer(Root, Bits);
		Writer.AppendInt32(Root, NumRows);
		Writer.AppendInt32(Root, NumRows);
		Writer.AppendInt32(Root, INDEX_NONE); // first free index
		Writer.AppendInt32(Root, 0);          // free count

		const int32 Hash = Writer.NewSection(4);
		for (const int32 Head : Buckets)
		{
			Writer.AppendInt32(Hash, Head);
		}
		Writer.AppendPointer(Root, Hash);
		Writer.AppendInt32(Root, HashSize);
		Writer.AppendInt32(Root, 0);
	}
	else
	{
		Writer.AppendZeros(Root, 32);
		Writer.AppendInt32(Root, INDEX_NONE);
		Writer.AppendInt32(Root, 0);
		Writer.AppendZeros(Root, 16);
	}

	// Row layout.
	const int32 NumFields = Layout.Fields.Num();
	if (NumFields > 0)
	{
		const int32 Definition = Writer.NewSection(4);
		for (const FField& Field : Layout.Fields)
		{
			Writer.AppendName(Definition, Field.Name);
			Writer.AppendInt32(Definition, Field.TypeCode);
		}
		Writer.AppendPointer(Root, Definition);
		Writer.AppendInt32(Root, NumFields);
		Writer.AppendInt32(Root, NumFields);
	}
	else
	{
		Writer.AppendZeros(Root, 16);
	}

	// Rows, then everything they point to.
	if (NumRows > 0)
	{
		const int32 RowSection = Writer.NewSection(Layout.RowAlignment);
		Writer.AppendPointer(Root, RowSection);
		Writer.AppendInt32(Root, NumRows);
		Writer.AppendInt32(Root, NumRows);
		for (int32 Index = 0; Index < NumRows; ++Index)
		{
			const int32 Base = Writer.SectionSize(RowSection);
			for (const FField& Field : Layout.Fields)
			{
				Writer.PadSectionTo(RowSection, Base + Field.Offset);
				Writer.AppendField(RowSection, Field, Rows[Index]);
			}
			Writer.PadSectionTo(RowSection, Base + Layout.RowSize);
		}
	}
	else
	{
		Writer.AppendZeros(Root, 16);
	}

	Writer.Flatten(Out);
	return true;
}
}
