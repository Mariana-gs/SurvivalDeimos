// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.generated.h"

UCLASS()
class SURVIVALDEIMOS_API APersonagemTPS : public ACharacter{
	
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagemTPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmCamera;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AArma> BP_Rifle;

	void MyCrouch();

	void MyUnCrouch();

	UPROPERTY(BlueprintReadOnly, Category = "Jump")
		bool bIsJumping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
		float Health;

	void Jump();

	void StopJump();

	void Atirar();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetHealth(float Dano);

	UFUNCTION()
		float GetHealth();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
		bool bIsDead;

	class AArma* ArmaPlayer;

};
