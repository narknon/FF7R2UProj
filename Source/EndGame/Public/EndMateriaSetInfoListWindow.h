#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMateriaSetInfoListWindow.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndMateriaSetInfoListWindow : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* InfoList_1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* InfoList_2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndUserWidget* InfoList_3;
    
    UEndMateriaSetInfoListWindow();

};

