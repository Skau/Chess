// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessGameModeBase.h"
#include "Engine/World.h"
#include "Board.h"
#include "ChessAI.h"
#include "ChessPiece.h"
#include "TimerManager.h"


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

	FActorSpawnParameters ActorSpawnParameters;
	ChessAI = GetWorld()->SpawnActor<AChessAI>(ActorSpawnParameters);
}

void AChessGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChessGameModeBase::StartGame(bool IsPlayingAgainstPlayer)
{
	GameBoard->SpawnChessPieces();
	bGameIsActive = true;
	bAgainstPlayer = IsPlayingAgainstPlayer;

	//if (!bAgainstPlayer)
	//{

	//}
}

void AChessGameModeBase::ToggleTurn()
{
	if (!bGameIsOver)
	{
		if (bAgainstPlayer)
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
		else
		{
			if (bIsWhiteTurn)
			{
				bIsWhiteTurn = false;
				// AI
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AChessGameModeBase::ResetTimer, 0.1f);

			}
			else
			{
				bIsWhiteTurn = true;
			}
		}
	}
}

void AChessGameModeBase::ResetTimer()
{ 
	ChessAI->StartRound(GameBoard);
}

