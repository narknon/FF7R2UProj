#pragma once
#include "CoreMinimal.h"
#include "EEndBattleNeoBahaBattleMode.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU2050BaseController.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleAISU2050BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> CommonAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BoosterAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BladeAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OverDriveBoosterAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> OverDriveBladeAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ChangeBladeModeAbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ChangeBoosterModeAbilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CommandBladeModebilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CommandBoosterModebilityID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MoogleSummonAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EXModeTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PathFindHeight;
    
public:
    AEndBattleAISU2050BaseController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetBattleMode(EEndBattleNeoBahaBattleMode BattleMode);
    
    UFUNCTION(BlueprintCallable)
    void OnChangeToBoosterMode();
    
    UFUNCTION(BlueprintCallable)
    void OnChangeToBladeMode();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EEndBattleNeoBahaBattleMode GetCurrentBattleMode();
    
    UFUNCTION(BlueprintCallable)
    bool ChangeBattleMode(EEndBattleNeoBahaBattleMode nextBattleMode, bool swapAbility);
    
};

