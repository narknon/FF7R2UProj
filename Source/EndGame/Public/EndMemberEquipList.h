#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndMemberEquipList.generated.h"

class UEndMemberEquipListCell;

UCLASS(Blueprintable, EditInlineNew)
class UEndMemberEquipList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberEquipListCell* Equip_01;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberEquipListCell* Equip_02;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberEquipListCell* Equip_03;
    
    UEndMemberEquipList();

};

