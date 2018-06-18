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

	BlackPawnsLost = 0;
	BlackRooksLost = 0;
	BlackKnightsLost = 0;
	BlackBishopsLost = 0;
	BlackQueenLost = 0;
	WhitePawnsLost = 0;
	WhiteRooksLost = 0;
	WhiteKnightsLost = 0;
	WhiteBishopsLost = 0;
	WhiteQueenLost = 0;
}

void AChessGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChessGameModeBase::StartGame()
{
	GameBoard->SpawnChessPieces();
	bGameIsActive = true;
}

void AChessGameModeBase::ToggleTurn()
{
	if (bIsWhiteTurn)
	{
		bIsWhiteTurn = false;
	}
	else
	{
		bIsWhiteTurn = true;
	}
}