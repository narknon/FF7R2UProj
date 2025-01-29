#include "EndEquipInfoDetailMateria.h"

UEndEquipInfoDetailMateria::UEndEquipInfoDetailMateria() {
    this->EndCanvasPanel_0 = NULL;
    this->MateriaInfoBox = NULL;
    this->MateriaInfoList = NULL;
    this->Txt_MateriaName = NULL;
    this->Txt_AttributeTitle = NULL;
    this->Txt_Attribute = NULL;
    this->Txt_StatusTitle = NULL;
    this->Txt_Status = NULL;
    this->MovieBillboard = NULL;
    this->Txt_MateriaInfo = NULL;
    this->Txt_MateriaInfo_summon = NULL;
}

void UEndEquipInfoDetailMateria::OnMateriaSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndEquipInfoDetailMateria::OnMateriaMeasureItem(int32 CellIndex) {
    return FVector2D{};
}


