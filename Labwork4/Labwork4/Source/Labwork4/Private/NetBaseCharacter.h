// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "Net/UnrealNetwork.h"
#include "NetGameInstance.h"
#include "NetBaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	BP_FACE = 0,
	BP_HAIR = 1,
	BP_CHEST = 2,
	BP_HANDS = 3,
	BP_LEGS = 4,
	BP_BEARD = 5,
	BP_EYEBROWS = 6,
	BP_BODYTYPE = 7,
	BP_COUNT = 8,
};

USTRUCT(BlueprintType)
struct FSMeshAssetList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> ListSkeletal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> ListStatic;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInfoChanged, ANetBaseCharacter*, Player);
// since this acts as a delegate, this is now a custom class, so we name it with F

UCLASS()
class ANetBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANetBaseCharacter();

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FString GetCustomizationData();
	void ParseCustomizationData(FString Data);

	UFUNCTION(BlueprintCallable)
	void ChangeBodyPart(EBodyPart index, int value, bool DirectSet);

	//UFUNCTION(BlueprintCallable)
	//void ChangeGender(bool isFemale);

	UFUNCTION(Server, Reliable)
	void SubmitPlayerInfoToServer(FSPlayerInfo Info);

	// we make "OnPlayerInfoChanged" a UPROPERTY with BlueprintAssignable and with type FOnPlayerInfoChanged since its now a delegate
	UPROPERTY(BlueprintAssignable)
	FOnPlayerInfoChanged OnPlayerInfoChanged;

	//Timer for waiting PlayerState
	UFUNCTION()
	void CheckPlayerState();

	UFUNCTION()
	void CheckPlayerInfo();

	bool PlayerInfoReceived;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartFace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartBeard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartEyes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartHands;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PartLegs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PartEyebrows;



private:

	static FSMeshAssetList* GetBodyPartList(EBodyPart part, bool isFemale);

	void UpdateBodyParts();

	int BodyPartIndices[EBodyPart::BP_COUNT];

	FTimerHandle ClientDataCheckTimer;

};
