// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessAI.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameModeBase.h"
#include "ChessPiece.h"
#include "Board.h"
#include "Tile.h"

// Sets default values
AChessAI::AChessAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChessAI::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AChessGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AChessAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChessAI::StartRound(ABoard *& GameBoard)
{
	auto Moves = FindAllPossibleMoves(GameBoard);

	int MoveIndex = FMath::RandRange(0, GameBoard->GetAllBlackPieces().Num() - 1);

	if (Moves.Num() >= MoveIndex)
	{
		auto Piece = Moves[MoveIndex].ChessPiece;

		auto Tile = Moves[MoveIndex].PossibleTileToMove;
		
		MovePiece(Moves[MoveIndex]);

		for (auto& Move : Moves)
		{
			Move.PossibleTileToMove->SetDefaultMaterial();
		}
		Moves.Empty();
	}
}

void AChessAI::MovePiece(FMove& Move)
{
	if (Move.ChessPiece && Move.PossibleTileToMove)
	{
		Move.ChessPiece->MoveToNewTile(Move.PossibleTileToMove);
	}
		GameMode->ToggleTurn();
}

TArray<FMove> AChessAI::FindAllPossibleMoves(ABoard*& GameBoard)
{
	TArray<FMove> AllPossibleMoves;
	if (GameMode)
	{
		FMove NewMove;
		NewMove.ChessPiece = nullptr;
		NewMove.PossibleTileToMove = nullptr;
		for (auto& Piece : GameBoard->GetAllBlackPieces())
		{
			for (auto& Tile : Piece->GetAllPossibleTiles())
			{
				Tile->SetIsPossibleMoveLocation(true);
				NewMove.ChessPiece = Piece;
				NewMove.PossibleTileToMove = Tile;

				AllPossibleMoves.Add(NewMove);
			}
		}
	}
	return AllPossibleMoves;
}
