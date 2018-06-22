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
	// Random number in range
	int MoveIndex = FMath::RandRange(0, GameBoard->GetAllBlackPieces().Num() - 1);
	//UE_LOG(LogTemp, Warning, TEXT("Index: %i"), MoveIndex)
	//UE_LOG(LogTemp, Warning, TEXT("AllPossibleMoves.Num(): %i"), AllPossibleMoves.Num())
	if (Moves.Num() >= MoveIndex)
	{
		auto Piece = Moves[MoveIndex].ChessPiece;
		//UE_LOG(LogTemp, Warning, TEXT("Piece name: %s"), *Piece->GetName())
		//Piece->SetblackMaterialHighlighted();

		auto Tile = Moves[MoveIndex].PossibleTileToMove;
		//UE_LOG(LogTemp, Warning, TEXT("Tile name: %s"), *Tile->GetTileName().ToString())
		//Tile->SetHighlightedPossibleMoveMaterial();
		
		MovePiece(Moves[MoveIndex]);

		for (auto& Move : Moves)
		{
			Move.PossibleTileToMove->SetDefaultMaterial();
		}
		Moves.Empty();
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Out of range"))
	}
}

void AChessAI::MovePiece(FMove& Move)
{
	if (Move.ChessPiece && Move.PossibleTileToMove)
	{
		// Move to the new tile
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
