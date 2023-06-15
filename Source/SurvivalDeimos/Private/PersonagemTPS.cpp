// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
APersonagemTPS::APersonagemTPS(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmCamera"));
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 40.f, 50.f));
	SpringArmCamera->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArmCamera);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APersonagemTPS::BeginPlay(){
	Super::BeginPlay();

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

}

