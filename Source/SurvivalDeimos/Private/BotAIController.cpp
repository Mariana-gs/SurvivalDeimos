// Fill out your copyright notice in the Description page of Project Settings.


#include "BotAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "BotCharacter.h"
#include "Engine/Engine.h"
#include "Arma.h"



ABotAIController::ABotAIController(){
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensingComp"));
	PawnSensingComp->SensingInterval = 0.25f;
	PawnSensingComp->bOnlySensePlayers = true;
	PawnSensingComp->SetPeripheralVisionAngle(180.f);
	PawnSensingComp->SightRadius = 3000.f;

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComp"));
}

void ABotAIController::OnPossess(APawn* InPawn){
	Super::OnPossess(InPawn);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAIController::OnSeePawn);
	if (BehaviorTree) {
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
		BlackBoardComp->SetValueAsBool("DeveAndar", true);
	}
}

void ABotAIController::OnSeePawn(APawn* SensedPawn){

	ABotCharacter* Bot = Cast <ABotCharacter>(GetPawn());

	if (!(Bot->bIsDead)) {

		if (BlackBoardComp && SensedPawn) {
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Estou te Vendo"));
			BlackBoardComp->SetValueAsObject("Inimigo", SensedPawn);
			BlackBoardComp->SetValueAsBool("DeveAndar", false);

			BlackBoardComp->SetValueAsBool("DeveAndar", false);

			Bot->ArmaInimigo->Atirar();
		}
	}
}
