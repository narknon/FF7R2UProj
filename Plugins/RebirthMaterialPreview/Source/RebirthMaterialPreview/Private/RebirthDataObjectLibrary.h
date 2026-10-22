#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthDataObjectLibrary.generated.h"

// Editor scripting (Python, Blueprint utilities) for the game's data objects: import, make editable, edit rows,
// and write the cooked form to a file for checking.
UCLASS()
class URebirthDataObjectLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Imports a game data object (for example /Game/DataObject/Resident/CharaSpec) as an editable asset. TargetPackageName
	// defaults to the game path; GamePaksDirectory defaults to the saved or usual game location.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool ImportDataObjectFromGame(const FString& GamePackageName, const FString& GamePaksDirectory, const FString& TargetPackageName, FString& Message);

	// Makes a cooked data object in the project editable in place.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool MakeDataObjectEditable(const FString& PackageName, FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static TArray<FName> GetDataObjectRowNames(const FString& PackageName);

	// Field value as text (the editor's copy format), or empty when the row or field does not exist.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static FString GetDataObjectRowField(const FString& PackageName, FName RowName, FName FieldName);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool SetDataObjectRowField(const FString& PackageName, FName RowName, FName FieldName, const FString& Value, FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool DuplicateDataObjectRow(const FString& PackageName, FName SourceRowName, FName NewRowName, FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool RemoveDataObjectRow(const FString& PackageName, FName RowName, FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool SaveDataObject(const FString& PackageName, FString& Message);

	// Saves the data object the way cooking does (WindowsNoEditor) to Filename (.uasset, with its .uexp beside it).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool CookDataObjectToFile(const FString& PackageName, const FString& Filename, FString& Message);

	// CharaSpec tables: problems that would leave the game on its loading screen (missing data asset entries, motion
	// folders or anim sets, rows referred to but not in the table). Rows empty = the rows that differ from the game's table.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static TArray<FString> CheckCharaSpecRows(const FString& PackageName, const TArray<FName>& Rows);

	// Checks every data object in the game against this project: each is read into rows, saved and loaded the way an
	// editable asset is, and cooked again, and the result must be the game's own bytes. Writes a JSON report to ReportFile.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Data Objects")
	static bool VerifyGameDataObjects(const FString& GamePaksDirectory, const FString& ReportFile, FString& Message);
};
