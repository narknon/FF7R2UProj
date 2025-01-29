#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "EEquipmentType.h"
#include "EPlayerStatus.h"
#include "EPlayerStreamType.h"
#include "EPlayerType.h"
#include "EndPartyAPI.generated.h"

class AActor;
class AEndCharacter;

UCLASS(Blueprintable, MinimalAPI)
class UEndPartyAPI : public UObject {
    GENERATED_BODY()
public:
    UEndPartyAPI();

    UFUNCTION(BlueprintCallable)
    static void StartPlayerStream(EPlayerStreamType Type);
    
    UFUNCTION(BlueprintCallable)
    static void SetPlayerStatus(EPlayerType Type, EPlayerStatus Status);
    
    UFUNCTION(BlueprintCallable)
    static void SetPlayerActor(EEquipmentType Equipment, EPlayerType Type, AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static void SetPartyLeaderType(EPlayerType InLeader, bool bIsInputTrigered, bool bForce);
    
    UFUNCTION(BlueprintCallable)
    static void SetPartyLeader(AActor* InLeader, bool bIsInputTrigered);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleSlotIndex(EPlayerType Type, int32 Slot);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleAway(EPlayerType Type, bool bFlag);
    
    UFUNCTION(BlueprintCallable)
    static void ResetPlayerPosition();
    
    UFUNCTION(BlueprintCallable)
    static bool IsReserveMember(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static bool IsFinishPlayerStream();
    
    UFUNCTION(BlueprintCallable)
    static bool IsBattleMember(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static bool IsAllPartyMember(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
    static void InitPartyLevel(const UObject* WorldContextObject);
    
    UFUNCTION(BlueprintCallable)
    static EPlayerType GetReserveMemberType(int32 Slot);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetReserveMembers();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetReserveMemberCount();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetReserveMember(int32 Index);
    
    UFUNCTION(BlueprintCallable)
    static EPlayerStatus GetPlayerStatus(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static FName GetPlayerActorName(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static AActor* GetPlayerActor(EEquipmentType Equipment, EPlayerType Type);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPartyMemberCountForPartyStatus(EPlayerStatus findPlayerStatus);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EPlayerType GetPartyLeaderType();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetPartyLeaderOrVehicle(bool bIsFatMoogleIgnore);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetPartyLeaderName();
    
    UFUNCTION(BlueprintCallable)
    static TArray<EPlayerType> GetEquipmentMenuMembers();
    
    UFUNCTION(BlueprintCallable)
    static int32 GetBattleSlotIndex(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static EPlayerType GetBattleMemberType(int32 Slot);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetBattleMembers();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBattleMemberCount();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetBattleMember(int32 Index);
    
    UFUNCTION(BlueprintCallable)
    static bool GetBattleAway(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable)
    static EPlayerType GetAllPartyMemberType(int32 Slot);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetAllPartyMembers();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAllPartyMemberCount();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetAllPartyMember(int32 Index);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAliveBattleMemberCount();
    
    UFUNCTION(BlueprintCallable)
    static void CallTeleported(const FVector& NewLocation, AActor* InLeader);
    
};

