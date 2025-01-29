#include "EndCategoryTitleMember.h"

UEndCategoryTitleMember::UEndCategoryTitleMember() {
    this->Txt_MainTitle = NULL;
    this->CategorySwitch = NULL;
    this->Icon_Member = NULL;
}

void UEndCategoryTitleMember::OnSelectItemSetupItem(UWidget* ItemWidget, int32 CellIndex) {
}

FVector2D UEndCategoryTitleMember::OnSelectItemMeasureItem(int32 CellIndex) {
    return FVector2D{};
}


