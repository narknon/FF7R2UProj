#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndGlyphInfo.h"
#include "EndFont.generated.h"

class UTexture2D;

UCLASS(Blueprintable)
class ENDGAME_API UEndFont : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UTexture2D*> Textures;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<uint16, FEndGlyphInfo> GlyphTable;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FString, uint16> IconTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Size;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OutlineSize;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<UTexture2D*> AllTextures;
    
public:
    UEndFont();

};

