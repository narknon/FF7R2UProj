#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "HSFLipSyncDataPack.h"

#include "HSFLipSyncDataPackFactory.generated.h"

UCLASS()
class HSFLIPSYNCEDITOR_API UHSFLipSyncDataPackFactory : public UFactory {
    GENERATED_BODY()

public:
    UHSFLipSyncDataPackFactory();
  
    virtual uint32 GetMenuCategories() const override;
    virtual FText GetDisplayName() const override;
    virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
    virtual bool ShouldShowInNewMenu() const override;
    virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};


