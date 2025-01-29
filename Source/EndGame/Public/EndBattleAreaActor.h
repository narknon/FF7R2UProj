#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavPriorRegistInfo.h"
#include "AI/Navigation/NavRelevantInterface.h"
#include "EndBattleAreaActor.generated.h"

class UEndBattleAreaBoxComponent;
class UEndCationAreaBoxComponent;
class UEndNavModifierComponent;

UCLASS(Blueprintable)
class AEndBattleAreaActor : public AActor, public INavRelevantInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName battleSceneID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> SeriesBattleIDs;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBattleAreaBoxComponent* EndBattleAreaBoxComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCationAreaBoxComponent* EndCationAreaBoxComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* BattleModifierVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* CationModifierVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ExtendedBattleModifierVolume;
    
protected:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint64> AffectedPolysCacheRef;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNavPriorRegistInfo NavPriorInfo;
    
public:
    AEndBattleAreaActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

