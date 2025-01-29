#include "EndRecastNavMesh.h"

AEndRecastNavMesh::AEndRecastNavMesh(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bSortNavigationAreasByCost = true;
    this->bDrawNavAreaAll = true;
    this->bDrawNavAreaBuffer = false;
    this->bDrawCover = false;
    this->bDrawBattleArea = false;
    this->bDrawCationArea = false;
    this->bDrawExtendedBattleArea = false;
    this->bDrawDynamicBattleArea = false;
    this->bDrawTerritory = false;
    this->bDrawExtendedTerritory = false;
    this->bDrawSwampyLand = false;
    this->bDrawSandSwampyLand = false;
    this->bDrawDesert = false;
    this->bDrawShoal = false;
    this->bDrawSea = false;
    this->bDrawMountain = false;
    this->bDrawRiver = false;
    this->bDrawWorldGeneralJump = false;
    this->bDrawWater = false;
    this->bDrawWorldGeneralJumpToPlane = false;
    this->bDrawPartyAttr = false;
    this->bDrawNPCAttr = false;
    this->bDrawEnemyAttr = false;
    this->bDrawSubPartyAttr = false;
    this->bDrawWildAnimal = false;
    this->bDrawHub = false;
    this->bDrawTinyBronco = false;
    this->bDrawFieldAction = false;
    this->bDrawHookShot = false;
    this->bDrawFieldActionLink = false;
    this->bDrawRedLaser = false;
    this->bDrawImpassable = false;
    this->bDrawImpassable2 = false;
    this->bDrawObstacle = false;
    this->bDrawCinemaObstacle = false;
    this->bDrawAddAttribute = false;
    this->bDrawAddAttribute2 = false;
    this->bDrawAddAttribute3 = false;
    this->bDrawAddAttribute4 = false;
    this->bDrawIgnore = false;
    this->bDrawVersatile = false;
    this->bDrawVersatile2 = false;
    this->bDrawVersatile3 = false;
    this->bDrawVersatile4 = false;
    this->bDrawInDoor = false;
    this->bDrawPathWay = false;
    this->bDrawCentralPathWay = false;
    this->bDrawNarrowLane = false;
    this->bDrawDefault = false;
    this->bDrawBattleSceneFilter = false;
    this->NavMeshVersion = 0;
    this->ObjectCount = 0;
}


