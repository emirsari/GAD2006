// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


APlayerCharacter::APlayerCharacter() : RunningSpeed(600.0f), CrouchingSpeed(150.f), MaxStamina(100.0f), StaminaDrainRate(10.0f),
StaminaGainRate(15.0f), CharacterType(ECharacterType::CharT_Player), bGettingHit(false), Stamina(100.0f), bHoldingRunKey(false),
bStaminaDrained(false), bReleased(false), bPressedCrouchKey(false)

{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false; 
	bUseControllerRotationYaw = false;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchingSpeed;
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &APlayerCharacter::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &APlayerCharacter::RunReleased);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpPressed);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &APlayerCharacter::CrouchPressed);

	PlayerInputComponent->BindAction("LightAttack", EInputEvent::IE_Pressed, this, &APlayerCharacter::LightAttackPressed);
	PlayerInputComponent->BindAction("Block", EInputEvent::IE_Pressed, this, &APlayerCharacter::BlockPressed);
	PlayerInputComponent->BindAction("Block", EInputEvent::IE_Released, this, &APlayerCharacter::BlockReleased);
	PlayerInputComponent->BindAction("HeavyAttack", EInputEvent::IE_Pressed, this, &APlayerCharacter::HeavyAttackPressed);
}

float APlayerCharacter::getStamina()
{
	return Stamina;
}

void APlayerCharacter::setStamina(float NewStamina)
{
	Stamina = NewStamina;
}

float APlayerCharacter::getMaxStamina()
{
	return MaxStamina;
}

void APlayerCharacter::setHealth(float NewPlayerHealth)
{
	Health = NewPlayerHealth;
}

void APlayerCharacter::HitReact_Implementation(APlayerCharacter* HitActor)
{
	if (!bDead && !bGettingHit && (HitActor->bBlocking == false)) {

		bGettingHit = true;
		HitActor->PlayAnimMontage(HitReactionAnim, 1.0f);
		HitActor->Health -= 20.0f;
	
	}

	GetWorldTimerManager().SetTimer(TimerHandle_PlayerCharacter, this, &APlayerCharacter::OnTimerEnd_HitReact, 1.0f, false);

}

void APlayerCharacter::HitDetect()
{

	FVector StartLocation = GetMesh()->GetSocketLocation("hand_r");
	FVector EndLocation = StartLocation;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this); // add owner of the class to the "ignored actors" array GetOwner()
	TArray<FHitResult> HitArray;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;

	bool bHasHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, EndLocation, 20.0f,
		UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnore, EDrawDebugTrace::None, 
		HitArray, true, FLinearColor::Gray, FLinearColor::Blue, 5.0f);

	if (bHasHit) {

		for (FHitResult HitResult : HitArray) { // for each hit result 

			APlayerCharacter* HitCharacter = Cast<APlayerCharacter>(HitResult.GetActor()); // get "hit actor"
			AController* PlayerController = HitCharacter->GetInstigator()->GetController();

			//will be able to damage if actor is not of the same character type
			if (HitCharacter->CharacterType != this->CharacterType) {
				HitReact_Implementation(HitCharacter);
			}
		}
		
	}
}

void APlayerCharacter::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector ForwardDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Amount);

}

void APlayerCharacter::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector RightDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, Amount);

}

void APlayerCharacter::RunPressed()
{

	bHoldingRunKey = true;
	UpdateMovementParams();

}

void APlayerCharacter::RunReleased()
{

	bHoldingRunKey = false;
	UpdateMovementParams();

}

void APlayerCharacter::JumpPressed()
{
	
	float JumpStamina = 25.f;

	if (!((Stamina-JumpStamina) <= 0.f) && ACharacter::bWasJumping != true) {
		ACharacter::Jump();
		Stamina -= JumpStamina;
		//GetCharacterMovement()->SetJumpAllowed(false);
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Not enough stamina to JUMP !")));
	}

	//GetCharacterMovement()->SetJumpAllowed(true);
		
}

void APlayerCharacter::CrouchPressed()
{

	if (bPressedCrouchKey) {
		APlayerCharacter::Crouch(false);
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Crouching")));
		bPressedCrouchKey = !bPressedCrouchKey;
	}
	else {
		APlayerCharacter::UnCrouch(false);
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("UNcrouching")));
		bPressedCrouchKey = !bPressedCrouchKey;
	}
	
	
}

void APlayerCharacter::LightAttackPressed()
{
	if (!bAttacking) {
		bAttacking = true;
		DoLightAttack(1.6f, 1.0f, LightAttackMontage_1, LightAttackMontage_2, 2);
	}
	
}

void APlayerCharacter::HeavyAttackPressed()
{
	if (!bAttacking) {
		bAttacking = true;
		DoHeavyAttack(1.6f, 1.0f, HeavyAttackAnim);
	}
}

void APlayerCharacter::BlockPressed()
{

	if (CharacterType != ECharacterType::CharT_Enemy) {
		bBlocking = true;
	}
	
}

void APlayerCharacter::BlockReleased()
{
	if (CharacterType != ECharacterType::CharT_Enemy) {
		bBlocking = false;
	}
	
}

void APlayerCharacter::DoLightAttack(float AnimPlayRate, float AnimRetriggerDelay,
	UAnimMontage* AnimInstance_1, UAnimMontage* AnimInstance_2, int AnimCount)
{
	if (bDead) return;

	if (bAttacking) {
		PlayAnimMontage(AnimInstance_1, AnimPlayRate);
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Attacking")));
	}

	GetWorldTimerManager().SetTimer(TimerHandle_PlayerCharacter, this, &APlayerCharacter::OnTimerEnd_Attack, 1.0f, false);

}

void APlayerCharacter::OnTimerEnd_Attack()
{
	bAttacking = false;
}

void APlayerCharacter::OnTimerEnd_HitReact()
{
	bAttacking = false;
	bGettingHit = false;
}

void APlayerCharacter::DoHeavyAttack(float AnimPlayRate, float AnimRetriggerDelay, UAnimMontage* AnimInstance)
{
	if (bDead) return;

	if (bAttacking) {
		PlayAnimMontage(AnimInstance, AnimPlayRate);
		//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("HeavyAttacking")));
	}

	GetWorldTimerManager().SetTimer(TimerHandle_PlayerCharacter, this, &APlayerCharacter::OnTimerEnd_Attack, 1.0f, false);
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if ((GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) && !(GetCharacterMovement()->Velocity.IsZero()) && (bHoldingRunKey) && (bStaminaDrained == false)) {

		Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);

		if (Stamina <= 0.0f) {
			bStaminaDrained = true;
			UpdateMovementParams();
		}

	}
	else {

		Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);

		if (Stamina >= MaxStamina) {
			bStaminaDrained = false;
			UpdateMovementParams();
		}

	}
	//GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::White, FString::Printf(TEXT("Stamina: %f"), Stamina));

}

void APlayerCharacter::UpdateMovementParams()
{
	GetCharacterMovement()->MaxWalkSpeed = bHoldingRunKey && !bStaminaDrained ? RunningSpeed : WalkingSpeed;
}


