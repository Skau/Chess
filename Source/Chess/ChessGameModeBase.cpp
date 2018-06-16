// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessGameModeBase.h"
#include "Engine/World.h"
#include "Board.h"


AChessGameModeBase::AChessGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AChessGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;

	GameBoard = GetWorld()->SpawnActor<ABoard>(Board, SpawnParameters);
	if (GameBoard)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameBoard set!"))
	}
}

void AChessGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
