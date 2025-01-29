#pragma once
#include "CoreMinimal.h"
#include "DebugBootMenuShowListBoxDelegate.generated.h"

UDELEGATE(BlueprintCallable) DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDebugBootMenuShowListBox, TArray<FString>, InStringList, bool, AutoSelectSingleList);

