#pragma once

#include "CoreMinimal.h"
#include "EHSFLipMapShapeAttributeType.h"
#include "HSFLipMapShapeAttribute.h"
#include "HSFLipMapShape.h"

#include "HSFLipMapJSONStructures.generated.h"

// JSON-compatible structure for attributes
USTRUCT()
struct FHSFLipMapShapeAttributeJSON {
    GENERATED_BODY()

    UPROPERTY()
    FName Key;

    UPROPERTY()
    float Value;
};

// JSON-compatible structure for shapes
USTRUCT()
struct FHSFLipMapShapeJSON {
    GENERATED_BODY()

    UPROPERTY()
    FName Key;

    UPROPERTY()
    TArray<FHSFLipMapShapeAttributeJSON> Attributes;
};

// Root JSON structure
USTRUCT()
struct FHSFLipMapJSON {
    GENERATED_BODY()

    UPROPERTY()
    FString Type;

    UPROPERTY()
    FString Class;

    UPROPERTY()
    FName Name;

    UPROPERTY()
    FString version;

    UPROPERTY()
    TArray<FHSFLipMapShapeJSON> Shapes;
};
