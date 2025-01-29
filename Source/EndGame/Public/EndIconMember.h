#pragma once
#include "CoreMinimal.h"
#include "EndUserWidget.h"
#include "EndIconMember.generated.h"

class UEndCanvasPanel;
class UEndIconFace;
class UEndImage;

UCLASS(Blueprintable, EditInlineNew)
class UEndIconMember : public UEndUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndCanvasPanel* EndCanvasPanel_0;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_BattleLeader;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndIconFace* Icon_Face;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndImage* Icon_Lock;
    
    UEndIconMember();

};

