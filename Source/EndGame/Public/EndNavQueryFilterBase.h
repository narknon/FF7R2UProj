#pragma once
#include "CoreMinimal.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "EndNavQueryFilterBase.generated.h"

UCLASS(Blueprintable)
class UEndNavQueryFilterBase : public UNavigationQueryFilter {
    GENERATED_BODY()
public:
    UEndNavQueryFilterBase();

};

