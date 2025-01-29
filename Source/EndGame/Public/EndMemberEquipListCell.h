#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMemberEquipListCell.generated.h"

class UEndAbilityName;
class UEndIconItem;
class UEndImage;
class UEndMateriaListNew;
class UEndTextBlock;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberEquipListCell : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndTextBlock* Txt_Title;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Line1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaListNew* Materia_ListNew2;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconItem* Icon_Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndAbilityName* AbilityName;
    
    UEndMemberEquipListCell();

};

