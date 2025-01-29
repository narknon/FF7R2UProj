#pragma once
#include "CoreMinimal.h"
#include "EndChangeAppearanceSetting.h"
#include "EndCharacter.h"
#include "EndChangeAppearanceCharacter.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndChangeAppearanceCharacter : public AEndCharacter {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndChangeAppearanceSetting> ChangeAppearanceSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FEndChangeAppearanceSetting AppearanceResetSetting;
    
public:
    AEndChangeAppearanceCharacter(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void RequestChangeAppearance_ForceFinishAbility(int32 Index);
    
    UFUNCTION(BlueprintCallable)
    void RequestChangeAppearance(int32 Index, bool bImmediately);
    
};

