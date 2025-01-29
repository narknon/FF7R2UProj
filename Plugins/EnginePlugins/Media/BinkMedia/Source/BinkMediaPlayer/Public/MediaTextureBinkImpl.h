#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/Texture.h"
#include "MediaTextureImplInterface.h"
#include "MediaTextureBinkImpl.generated.h"

class UBinkMediaPlayer;

UCLASS(Blueprintable)
class BINKMEDIAPLAYER_API UMediaTextureBinkImpl : public UObject, public IMediaTextureImplInterface {
    GENERATED_BODY()
public:
    UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<TextureAddress> AddressX;
    
    UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<TextureAddress> AddressY;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UBinkMediaPlayer* MediaPlayer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool tonemap;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OutputNits;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Alpha;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool DecodeSRGB;
    
    UMediaTextureBinkImpl();


    // Fix for true pure virtual functions not being implemented
};

