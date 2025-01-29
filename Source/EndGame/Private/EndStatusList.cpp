#include "EndStatusList.h"

UEndStatusList::UEndStatusList() {
    this->Txt_Level_Num = NULL;
    this->Txt_HP_Num = NULL;
    this->Txt_Hp_Total = NULL;
    this->Txt_Hp_Difference = NULL;
    this->Txt_MP_Num = NULL;
    this->Txt_Mp_Total = NULL;
    this->Txt_Mp_Difference = NULL;
    this->StatusList = NULL;
    this->BtnGuide = NULL;
}

void UEndStatusList::OnStatusListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndStatusList::OnStatusListMeasureItem(int32 CellIndex) {
    return FVector2D{};
}

void UEndStatusList::OnAdditionalStatusListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


