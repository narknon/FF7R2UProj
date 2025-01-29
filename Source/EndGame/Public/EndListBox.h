#pragma once
#include "CoreMinimal.h"
#include "Input/Events.h"
#include "Types/SlateEnums.h"
#include "Layout/Margin.h"
#include "Components/Widget.h"
#include "Templates/SubclassOf.h"
#include "EndListBox.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndListBox : public UWidget {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSetupItem, UWidget*, ItemWidget, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedIndexChanged, int32, ItemIndex);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressedItem, int32, ItemIndex);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EOrientation> Orientation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UWidget> ContentClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UWidget> CursorClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ItemCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DesiredCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin SlotPadding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin CursorBoundsExtension;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnSetupItem OnSetupItem;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnPressedItem OnPressedItem;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOnSelectedIndexChanged OnSelectedIndexChanged;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> ContentWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UWidget*> CachedWidgets;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWidget* CursorWidget;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    UWidget* CachedCursor;
    
public:
    UEndListBox();

    UFUNCTION(BlueprintCallable)
    void SetSelectedIndexWithCause(int32 UserIndex, int32 SlotIndex, EFocusCause FocusCause);
    
    UFUNCTION(BlueprintCallable)
    void SetSelectedIndex(int32 UserIndex, int32 SlotIndex);
    
    UFUNCTION(BlueprintCallable)
    void SetPadding(FMargin InPadding);
    
    UFUNCTION(BlueprintCallable)
    void SetItemCount(int32 InItemCount);
    
    UFUNCTION(BlueprintCallable)
    void SetForceHovered(bool bInHovered);
    
    UFUNCTION(BlueprintCallable)
    void SetDesiredCount(int32 InDesiredCount);
    
    UFUNCTION(BlueprintCallable)
    void SetCursorBoundsExtension(FMargin InCursorBoundsExtension);
    
    UFUNCTION(BlueprintCallable)
    void RefreshItems();
    
    UFUNCTION(BlueprintCallable)
    void RefreshItem(int32 Index);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetSelectedIndex(int32 UserIndex) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetIsForceHovered() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWidget* GetCursorWidget() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWidget* GetChildAt(int32 Index) const;
    
};

