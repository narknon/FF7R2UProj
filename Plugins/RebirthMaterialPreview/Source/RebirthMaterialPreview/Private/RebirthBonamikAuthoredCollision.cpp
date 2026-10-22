#include "RebirthBonamikAuthoredCollision.h"

namespace
{
    float SegmentAlpha(const FVector& P, const FVector& A, const FVector& B)
    {
        const float LengthSquared = (B - A).SizeSquared();
        return LengthSquared > SMALL_NUMBER ? FMath::Clamp(FVector::DotProduct(P - A, B - A) / LengthSquared, 0.0f, 1.0f) : 0.0f;
    }
    bool TriangleWeights(const FVector& P, const FVector& A, const FVector& B, const FVector& C, FVector& Out)
    {
        const FVector V0=B-A, V1=C-A, V2=P-A;
        const float D00=FVector::DotProduct(V0,V0), D01=FVector::DotProduct(V0,V1), D11=FVector::DotProduct(V1,V1);
        const float Denom=D00*D11-D01*D01;
        if (FMath::Abs(Denom) < SMALL_NUMBER) return false;
        const float BWeight=(D11*FVector::DotProduct(V2,V0)-D01*FVector::DotProduct(V2,V1))/Denom;
        const float CWeight=(D00*FVector::DotProduct(V2,V1)-D01*FVector::DotProduct(V2,V0))/Denom;
        Out=FVector(1.0f-BWeight-CWeight,BWeight,CWeight);
        return Out.GetMin() >= -0.001f;
    }
}

void FRebirthBonamikAuthoredCollision::Reset() { Shapes.Reset(); Pairs.Reset(); }

bool FRebirthBonamikAuthoredCollision::AddAsset(const TArray<FSQEX_BonamikShapeDesc>& Source,
    const TArray<FSQEX_BonamikCollisionCliqueDesc>& Cliques, const TMap<FName, int32>& ParticleByBodyName)
{
    if (Source.Num() > 4096 || Shapes.Num()+Source.Num() > 4096 || Cliques.Num() > 4096) return false;
    const int32 First = Shapes.Num();
    TMap<uint32,int32> ShapeById;
    for (const FSQEX_BonamikShapeDesc& Original : Source)
    {
        FShape Shape;
        Shape.Type=Original.mType==TEXT("sphere") ? 1 : Original.mType==TEXT("capsule") ? 2 : Original.mType==TEXT("plane") ? 3 : 0;
        const bool bSingleBodyPlane=Shape.Type==3 && Original.bIsInfinity && Original.mBodies.Num()==1;
        if (!Shape.Type || (!bSingleBodyPlane && Original.mBodies.Num()!=Shape.Type) || ShapeById.Contains(Original.mShapeId)) return false;
        for (const FString& Name : Original.mBodies)
        {
            const int32* Index=ParticleByBodyName.Find(FName(*Name));
            if (!Index) return false;
            Shape.Points.Add(*Index);
        }
        for (const FString& Group : Original.mReceiverGroups) Shape.Receivers.AddUnique(FName(*Group));
        for (const FString& Group : Original.mRepulsorGroups) Shape.Repulsors.AddUnique(FName(*Group));
        if (!FMath::IsFinite(Original.mPlaneThickness) || !FMath::IsFinite(Original.mPlaneOffset) || !FMath::IsFinite(Original.mCapsuleConcaveRatio)) return false;
        Shape.Thickness=FMath::Clamp(FMath::Abs(Original.mPlaneThickness),0.0f,100.0f);
        Shape.Offset=FMath::Clamp(Original.mPlaneOffset,-100.0f,100.0f);
        Shape.ConcaveRatio=Original.mCapsuleConcaveRatio;
        Shape.bInverse=Original.bIsInverse;
        Shape.bInfinite=Original.bIsInfinity;
        ShapeById.Add(Original.mShapeId,Shapes.Num());
        Shapes.Add(MoveTemp(Shape));
    }
    TSet<uint64> PairKeys;
    auto AddPair=[&](int32 A,int32 B)
    {
        if (A==B) return;
        for (int32 P : Shapes[A].Points) if (Shapes[B].Points.Contains(P)) return; // same authored point never self-collides
        const uint64 Key=(static_cast<uint64>(A)<<32)|static_cast<uint32>(B);
        if (!PairKeys.Contains(Key)) { PairKeys.Add(Key); Pairs.Add({A,B}); }
    };
    for (int32 A=First; A<Shapes.Num(); ++A)
        for (int32 B=First; B<Shapes.Num(); ++B)
            for (FName Group : Shapes[A].Receivers)
                if (Shapes[B].Repulsors.Contains(Group)) { AddPair(A,B); break; }
    // Explicit cliques supply pairs that are intentionally absent from group tags.
    // Directional receiver/repulsor tags remain exact, never broadened by bone or group guesses.
    for (const FSQEX_BonamikCollisionCliqueDesc& Clique : Cliques)
        for (int32 I=0; I<Clique.mShapeIds.Num(); ++I)
            for (int32 J=I+1; J<Clique.mShapeIds.Num(); ++J)
            {
                const int32* A=ShapeById.Find(Clique.mShapeIds[I]);
                const int32* B=ShapeById.Find(Clique.mShapeIds[J]);
                if (!A || !B) return false;
                AddPair(*A,*B);
                AddPair(*B,*A);
            }
    return Pairs.Num()<=65536;
}

void FRebirthBonamikAuthoredCollision::Solve(TArray<FVector>& Positions,
    const TArray<float>& Radii, const TArray<float>& InverseMasses, const TArray<FQuat>& BodyRotations) const
{
    if (Positions.Num()!=Radii.Num() || Positions.Num()!=InverseMasses.Num() || Positions.Num()!=BodyRotations.Num()) return;
    for (const FPair& Pair : Pairs)
    {
        const FShape& Receiver=Shapes[Pair.Receiver];
        const FShape& Collider=Shapes[Pair.Repulsor];
        bool bIndicesValid=true;
        for (int32 Index : Receiver.Points) bIndicesValid &= Positions.IsValidIndex(Index);
        for (int32 Index : Collider.Points) bIndicesValid &= Positions.IsValidIndex(Index);
        if (!bIndicesValid) continue;
        TArray<FVector, TInlineAllocator<7>> Samples;
        for (int32 Index=0; Index<Receiver.Points.Num(); ++Index)
        {
            FVector Weights=FVector::ZeroVector; Weights[Index]=1.0f; Samples.Add(Weights);
        }
        if (Receiver.Type==2) Samples.Add(FVector(0.5f,0.5f,0.0f));
        if (Receiver.Type==3 && Receiver.Points.Num()==3)
        {
            Samples.Add(FVector(0.5f,0.5f,0.0f)); Samples.Add(FVector(0.0f,0.5f,0.5f));
            Samples.Add(FVector(0.5f,0.0f,0.5f)); Samples.Add(FVector(1.0f/3.0f));
        }
        for (const FVector& Weights : Samples)
        {
            FVector Location=FVector::ZeroVector;
            float Radius=Receiver.Type==3 ? Receiver.Thickness*0.5f : 0.0f;
            for (int32 I=0; I<Receiver.Points.Num(); ++I)
            {
                Location+=Positions[Receiver.Points[I]]*Weights[I];
                if (Receiver.Type!=3) Radius+=Radii[Receiver.Points[I]]*Weights[I];
            }
            if (Receiver.Type==3)
            {
                FVector SurfaceNormal=Receiver.Points.Num()==1 ? BodyRotations[Receiver.Points[0]].GetAxisY() :
                    FVector::CrossProduct(Positions[Receiver.Points[1]]-Positions[Receiver.Points[0]],
                    Positions[Receiver.Points[2]]-Positions[Receiver.Points[0]]).GetSafeNormal();
                if (Receiver.bInverse) SurfaceNormal=-SurfaceNormal;
                Location+=SurfaceNormal*Receiver.Offset;
            }
            FVector ColliderWeights=FVector::ZeroVector, Normal=FVector::ZeroVector;
            float Penetration=0.0f;
            const FVector A=Positions[Collider.Points[0]];
            if (Collider.Type==1 || Collider.Type==2)
            {
                float Alpha=0.0f;
                FVector Closest=A;
                float ColliderRadius=Radii[Collider.Points[0]];
                if (Collider.Type==2)
                {
                    const FVector B=Positions[Collider.Points[1]];
                    Alpha=SegmentAlpha(Location,A,B);
                    Closest=FMath::Lerp(A,B,Alpha);
                    ColliderRadius=FMath::Lerp(ColliderRadius,Radii[Collider.Points[1]],Alpha);
                }
                ColliderWeights=FVector(1.0f-Alpha,Alpha,0.0f);
                const FVector Delta=Location-Closest;
                const float Distance=Delta.Size();
                Normal=Distance>SMALL_NUMBER ? Delta/Distance : FVector::UpVector;
                // Authored inverse spheres/capsules bound the inside of a
                // volume. Keep the complete receiver sample inside its radius,
                // rather than treating it as an ordinary solid repulsor.
                // This is an explicit custom-preview interpretation; the
                // tapered-capsule closest-axis sample is still an approximation.
                if (Collider.bInverse)
                {
                    Penetration=Distance+Radius-ColliderRadius;
                    Normal=-Normal;
                }
                else Penetration=Radius+ColliderRadius-Distance;
            }
            else
            {
                const bool bBodyFramePlane=Collider.Points.Num()==1;
                const FVector B=bBodyFramePlane ? A : Positions[Collider.Points[1]];
                const FVector C=bBodyFramePlane ? A : Positions[Collider.Points[2]];
                // The original descriptor supplies only a body frame for this
                // infinite-plane form. Local +Y is an explicit custom-preview
                // convention, not a verified retail plane-axis contract.
                Normal=bBodyFramePlane ? BodyRotations[Collider.Points[0]].GetAxisY() : FVector::CrossProduct(B-A,C-A).GetSafeNormal();
                if (Normal.IsNearlyZero()) continue;
                if (Collider.bInverse) Normal=-Normal;
                const float SignedDistance=FVector::DotProduct(Location-A,Normal)-Collider.Offset;
                const FVector Projected=Location-Normal*(SignedDistance+Collider.Offset);
                if (bBodyFramePlane) ColliderWeights=FVector(1.0f,0.0f,0.0f);
                else if (!TriangleWeights(Projected,A,B,C,ColliderWeights))
                {
                    if (!Collider.bInfinite) continue;
                    ColliderWeights=FVector(1.0f/3.0f);
                }
                if (Collider.bInfinite)
                {
                    ColliderWeights.X=FMath::Max(0.0f,ColliderWeights.X);
                    ColliderWeights.Y=FMath::Max(0.0f,ColliderWeights.Y);
                    ColliderWeights.Z=FMath::Max(0.0f,ColliderWeights.Z);
                    ColliderWeights/=FMath::Max(ColliderWeights.X+ColliderWeights.Y+ColliderWeights.Z,SMALL_NUMBER);
                }
                Penetration=Radius+Collider.Thickness*0.5f-SignedDistance;
            }
            if (!FMath::IsFinite(Penetration) || Penetration<=0.0f || Normal.ContainsNaN()) continue;
            float Denominator=0.0f;
            for (int32 I=0; I<Receiver.Points.Num(); ++I)
                Denominator+=FMath::Square(Weights[I])*InverseMasses[Receiver.Points[I]];
            for (int32 I=0; I<Collider.Points.Num(); ++I)
                Denominator+=FMath::Square(ColliderWeights[I])*InverseMasses[Collider.Points[I]];
            if (Denominator<=SMALL_NUMBER) continue;
            const FVector Correction=Normal*(FMath::Min(Penetration,50.0f)/Denominator);
            for (int32 I=0; I<Receiver.Points.Num(); ++I)
                Positions[Receiver.Points[I]]+=Correction*(Weights[I]*InverseMasses[Receiver.Points[I]]);
            for (int32 I=0; I<Collider.Points.Num(); ++I)
                Positions[Collider.Points[I]]-=Correction*(ColliderWeights[I]*InverseMasses[Collider.Points[I]]);
        }
    }
}
