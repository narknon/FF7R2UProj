#pragma once
#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "EndNavLinkProxy.generated.h"

UCLASS(Blueprintable)
class AEndNavLinkProxy : public ANavLinkProxy {
    GENERATED_BODY()
public:
    AEndNavLinkProxy(const FObjectInitializer& ObjectInitializer);

};

