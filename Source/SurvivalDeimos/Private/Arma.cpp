// Fill out your copyright notice in the Description page of Project Settings.


#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/EngineTypes.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GamePlayStatics.h"
#include "Engine/World.h"
#include "Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.h"
#include "BotCharacter.h"


// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MuzzleEffect = nullptr;
	BloodImpact = nullptr;
	Impact = nullptr;
	MeshArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MeshArma"));
	DecalImpacto = nullptr;
	Sound = nullptr;
	

	ConstructorHelpers::FObjectFinder<USkeletalMesh>Mesh(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	if (Mesh.Succeeded()) {
		MeshArma->SetSkeletalMesh(Mesh.Object);
	}


	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(MeshArma, FName("MuzzleFlashSocket"));
	RootComponent = MeshArma;

	//Não é Recomendado Utilizar no construtor
	//Arrow->AttachToComponent(MeshArma, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MuzzleFlashSocket"));
	//Arrow->SetRelativeLocation(FVector(1.5f, 0.f, -1.2f));
	//Arrow->SetRelativeScale3D(FVector(0.3f, 0.8f, 0.7f));

}

void AArma::Atirar(){
	UArrowComponent* Arrow = FindComponentByClass<UArrowComponent>();
	if (Arrow) {
		FVector Inicio = Arrow->GetComponentLocation();
		FVector Direcao = Arrow->GetComponentRotation().Vector();
		FVector Fim = Inicio + (Direcao * 1000);

		FHitResult Info;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		Params.bTraceComplex = true;

		bool Hit = GetWorld()->LineTraceSingleByChannel(Info, Inicio, Fim, ECollisionChannel::ECC_Visibility, Params);

		if (Hit) {
			UE_LOG(LogTemp, Warning, TEXT("Acertou em Algo"));
			AActor* Actor = Info.GetActor();

			if (Actor->GetClass()->IsChildOf(ACharacter::StaticClass()) && BloodImpact) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodImpact, Info.Location, 
					Info.ImpactNormal.Rotation(), true);

				APersonagemTPS* Player = Cast<APersonagemTPS>(Actor);
				
				if (Player) {
					Player->SetHealth(10.f);
				}
				else {
					ABotCharacter* Inimigo = Cast<ABotCharacter>(Actor);
					if (Inimigo) {
						Inimigo->SetHealth(10.f);
					}
				}

			}else if (Impact) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, Info.Location, Info.ImpactNormal.Rotation(), true);

				FVector Tamanho = FVector(FMath::RandRange(10.f, 30.f));
				UGameplayStatics::SpawnDecalAttached(DecalImpacto, Tamanho, Info.GetComponent(), 
					NAME_None, Info.Location, Info.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 60.f );
			}
		}

		if (Sound) {
			UGameplayStatics::PlaySoundAtLocation(Arrow, Sound, Inicio);
		}

		//DrawDebugLine(GetWorld(), Inicio, Fim, FColor::Red, false, 5.f, (uint8)0, 1.0f);

		if (MuzzleEffect) {
			FVector Location = Arrow->GetComponentLocation();
			FRotator Rotation = Arrow->GetComponentRotation();
			FVector Scale = FVector(0.9f);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleEffect, Location, Rotation, Scale);
		}
	}
}

// Called when the game starts or when spawned
void AArma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

