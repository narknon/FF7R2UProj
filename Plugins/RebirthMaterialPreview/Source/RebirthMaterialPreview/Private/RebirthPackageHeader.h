#pragma once

#include "CoreMinimal.h"

/** The import and export tables of a package file (.uasset/.umap, cooked or editor format), read without loading it. */
namespace RebirthPackageHeader
{
	struct FImport
	{
		FName ClassPackage;
		FName ClassName;
		int32 OuterIndex = 0; // FPackageIndex: 0 = none (a package), < 0 = import, > 0 = export
		FName ObjectName;
	};

	struct FExport
	{
		int32 ClassIndex = 0;
		int32 SuperIndex = 0;
		int32 OuterIndex = 0;
		FName ObjectName;
		uint32 ObjectFlags = 0;
		bool bIsAsset = false;
	};

	struct FHeader
	{
		uint32 PackageFlags = 0;
		/** The package's name map. */
		TArray<FName> Names;
		TArray<FImport> Imports;
		TArray<FExport> Exports;

		bool IsCooked() const;

		/** Name of the class of an export (the import's or export's object name). */
		FName GetExportClassName(int32 ExportIndex) const;
		/** Package of the class of an export (for an import; the package itself for an export class). */
		FName GetExportClassPackage(int32 ExportIndex) const;
		/** "Package.Object" of an import (object path). */
		FString GetImportPath(int32 ImportIndex) const;
		/** The top package import of an import (INDEX_NONE when the chain leads into this package). */
		int32 GetImportPackage(int32 ImportIndex) const;
	};

	bool Read(const FString& Filename, FHeader& Out, bool bReadExports, FString& OutError);
}
