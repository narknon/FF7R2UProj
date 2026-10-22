#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikShapeDesc.h"
#include "SQEX_BonamikCollisionCliqueDesc.h"

// Custom preview contacts from the original shape definitions. Receiver
// surfaces use bounded samples; this does not reproduce the retail solver.
class FRebirthBonamikAuthoredCollision
{
public:
    void Reset();
    bool AddAsset(const TArray<FSQEX_BonamikShapeDesc>& Source,
        const TArray<FSQEX_BonamikCollisionCliqueDesc>& Cliques,
        const TMap<FName, int32>& ParticleByBodyName);
    void Solve(TArray<FVector>& Positions, const TArray<float>& Radii, const TArray<float>& InverseMasses,
        const TArray<FQuat>& BodyRotations) const;
    int32 GetShapeCount() const { return Shapes.Num(); }
    int32 GetPairCount() const { return Pairs.Num(); }
private:
    struct FShape
    {
        uint8 Type = 0; // sphere=1, capsule=2, plane=3
        TArray<int32> Points;
        TArray<FName> Receivers;
        TArray<FName> Repulsors;
        float Thickness = 0.0f;
        float Offset = 0.0f;
        float ConcaveRatio = 0.0f; // retained; custom preview uses straight tapered capsules
        bool bInverse = false;
        bool bInfinite = false;
    };
    struct FPair { int32 Receiver; int32 Repulsor; };
    TArray<FShape> Shapes;
    TArray<FPair> Pairs;
};
