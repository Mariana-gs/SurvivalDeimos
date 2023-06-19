// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotCharacter.generated.h"

UCLASS()
class SURVIVALDEIMOS_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AArma> BP_Rifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
		float Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetHealth(float Dano);

	UFUNCTION()
		float GetHealth();

	class AArma* ArmaInimigo;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
		bool bIsDead;


};
