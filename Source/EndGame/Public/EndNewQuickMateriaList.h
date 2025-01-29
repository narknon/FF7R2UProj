#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndNewQuickMateriaList.generated.h"

class UEndMateriaListAll;
class UEndMemberListCellContent;

UCLASS(Blueprintable, EditInlineNew)
class UEndNewQuickMateriaList : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMemberListCellContent* MemberList_CellContent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMateriaListAll* Materia_List_All;
    
    UEndNewQuickMateriaList();

};

