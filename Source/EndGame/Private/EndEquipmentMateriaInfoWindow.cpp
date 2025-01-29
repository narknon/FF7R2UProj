#include "EndEquipmentMateriaInfoWindow.h"

UEndEquipmentMateriaInfoWindow::UEndEquipmentMateriaInfoWindow() {
    this->StarInfoList = NULL;
    this->MateriaInfoBox = NULL;
    this->InfoWindow = NULL;
    this->Txt_Title = NULL;
    this->Txt_Title2 = NULL;
    this->MateriaInfoList = NULL;
    this->TipMovieBox = NULL;
    this->AbilityInfoBox = NULL;
    this->Txt_MovieInfo = NULL;
    this->Tips = NULL;
    this->Nut_Exp = NULL;
    this->GaugeBox = NULL;
    this->Gauge_Exp = NULL;
    this->Icon_Clear = NULL;
    this->Txt_Info = NULL;
    this->AccessoryInfoBox = NULL;
    this->Txt_AccessoryInfo = NULL;
    this->Txt_AttributeTitle = NULL;
    this->Txt_Attribute = NULL;
    this->Txt_StatusTitle = NULL;
    this->Txt_Status = NULL;
}

FVector2D UEndEquipmentMateriaInfoWindow::OnMeasureInfoListSize(int32 CellIndex) {
    return FVector2D{};
}

void UEndEquipmentMateriaInfoWindow::OnMateriaInfoListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

void UEndEquipmentMateriaInfoWindow::OnCoreListSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}


