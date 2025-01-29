#include "EndNavLinkProxy.h"

AEndNavLinkProxy::AEndNavLinkProxy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bSmartLinkIsRelevant = true;
}


