// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arma.generated.h"

UCLASS()
class SURVIVALDEIMOS_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

	UFUNCTION()
		void Atirar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* MeshArma;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UParticleSystem* BloodImpact;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UParticleSystem* Impact;

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UMaterialInterface* DecalImpacto;

	UPROPERTY(EditAnywhere, Category = "SoundEffect")
		class USoundBase* Sound;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
