// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"
#include "Public/WorldCollision.h"

// Sets default values
APersonagemTPS::APersonagemTPS(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmCamera"));
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->bEnableCameraLag = true;
	SpringArmCamera->CameraLagSpeed = 15.f; //Transição na hora de agachar
	SpringArmCamera->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmCamera);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->JumpZVelocity = 425.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APersonagemTPS::BeginPlay(){
	Super::BeginPlay();

	//Spawn Weapon
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ArmaPlayer = GetWorld()->SpawnActor<AArma>(BP_Rifle, FTransform(), Params);
	
	ArmaPlayer->AttachToComponent(Cast<USceneComponent>(GetMesh()), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));

}

void APersonagemTPS::MoveForward(float Value){
	AddMovementInput(GetActorForwardVector() * Value);
}

void APersonagemTPS::MoveRight(float Value){
	AddMovementInput(GetActorRightVector() * Value);
}

void APersonagemTPS::MyCrouch(){
	Crouch();
}

void APersonagemTPS::MyUnCrouch(){
	UnCrouch();
}

void APersonagemTPS::Jump(){
	bIsJumping = true;
}

void APersonagemTPS::StopJump(){
	bIsJumping = false;
}

void APersonagemTPS::Atirar(){
	ArmaPlayer->Atirar();
}

// Called every frame
void APersonagemTPS::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APersonagemTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APersonagemTPS::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APersonagemTPS::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APersonagemTPS::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APersonagemTPS::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &APersonagemTPS::MyCrouch);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Released, this ,&APersonagemTPS::MyUnCrouch);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APersonagemTPS::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APersonagemTPS::StopJump);
	PlayerInputComponent->BindAction("Atirar", EInputEvent::IE_Pressed, this, &APersonagemTPS::Atirar);

}

void APersonagemTPS::SetHealth(float Dano){
	if (Health > 0.f) {
		Health -= Dano;
	}else{
		bIsDead = true;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		check(PlayerController);
		PlayerController->GetPawn()->DisableInput(PlayerController);
	}
}

float APersonagemTPS::GetHealth(){
	return Health;
}

