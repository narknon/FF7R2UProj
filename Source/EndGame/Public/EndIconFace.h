#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndIconFace.generated.h"

class UEndImageSet;

UCLASS(Blueprintable, EditInlineNew)
class UEndIconFace : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImageSet* Icon_Face;
    
    UEndIconFace();

};

