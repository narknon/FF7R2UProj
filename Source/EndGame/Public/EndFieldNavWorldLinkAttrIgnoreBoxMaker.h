#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EndFieldNavWorldLinkAttrIgnoreBoxMaker.generated.h"

class UEndNavWorldLinkAttrIgnoreBoxComponent;

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldNavWorldLinkAttrIgnoreBoxMaker : public USceneComponent {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UEndNavWorldLinkAttrIgnoreBoxComponent*> NavWorldLinkAttrIgnoreBoxs;
    
    UEndFieldNavWorldLinkAttrIgnoreBoxMaker(const FObjectInitializer& ObjectInitializer);

};

