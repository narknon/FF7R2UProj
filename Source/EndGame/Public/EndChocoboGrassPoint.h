#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndTargetPoint.h"
#include "EndChocoboGrassPoint.generated.h"

class AActor;
class UCapsuleComponent;

UCLASS(Blueprintable, MinimalAPI)
class AEndChocoboGrassPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UCapsuleComponent* CollisionComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ChocoboGrassID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CharaSpecName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CharaSpec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SaveStoryFlag;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval ForceUpdateRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AActor* GrassActor;
    
public:
    AEndChocoboGrassPoint(const FObjectInitializer& ObjectInitializer);

};

