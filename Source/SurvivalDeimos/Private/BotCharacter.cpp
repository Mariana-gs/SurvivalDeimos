// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacter.h"
#include "Engine/World.h"
#include "Arma.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABotCharacter::ABotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABotCharacter::BeginPlay(){
	Super::BeginPlay();

	//Spawn Weapon
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ArmaInimigo = GetWorld()->SpawnActor<AArma>(BP_Rifle, FTransform(), Params);

	ArmaInimigo->AttachToComponent(Cast<USceneComponent>(GetMesh()), 
		FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));

}

// Called every frame
void ABotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABotCharacter::SetHealth(float Dano){
	if (Health > 0.f) {
		Health -= Dano;
	}
	else {
		bIsDead = true;
		SetLifeSpan(10.f);
		ArmaInimigo->Destroy();
	}
}

float ABotCharacter::GetHealth(){
	return Health;
}

