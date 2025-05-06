#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EditorReimportHandler.h"
#include "SQEXSEADMusic_Factory.generated.h"

/**
 * 
 */
UCLASS()
class ENDEDITOR_API USQEXSEADMusic_Factory : public UFactory
{
	GENERATED_BODY()
	
		USQEXSEADMusic_Factory();
	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Cntext, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
	virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
