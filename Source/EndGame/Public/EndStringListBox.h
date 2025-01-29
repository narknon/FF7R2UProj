#pragma once
#include "CoreMinimal.h"
#include "Types/SlateEnums.h"
#include "Components/Widget.h"
#include "Templates/SubclassOf.h"
#include "EndStringListBox.generated.h"

UCLASS(Blueprintable)
class UEndStringListBox : public UWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSetupItem, UWidget*, ItemWidget, int32, ItemIndex, const FString&, ItemString);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedItem, int32, ItemIndex);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EOrientation> Orientation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UWidget> ContentClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> Items;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DesiredCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnSetupItem OnSetupItem;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnPressedItem OnPressedItem;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> ContentWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> CachedWidgets;
    
public:
    UEndStringListBox();

    UFUNCTION(BlueprintCallable)
    void SetItems(const TArray<FString>& InItems);
    
    UFUNCTION(BlueprintCallable)
    void SetDesiredCount(int32 InDesiredCount);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetSelectedIndex(int32 UserIndex) const;
    
};

