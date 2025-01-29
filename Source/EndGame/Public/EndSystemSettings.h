#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndSystemSettings.generated.h"

UCLASS(Blueprintable, Config=EndSystem)
class ENDGAME_API UEndSystemSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Language;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName VoiceLanguage;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bKeyboardControlEnabled;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bMouseControlEnabled;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bMouseAndKeyboardControlShortcutsEnabled;
    
    UEndSystemSettings();

};

