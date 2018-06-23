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
	//Calculate etc..
	FMove Move = MiniMaxRoot(GameBoard, 2, false);

	MovePiece(Move);
}

void AChessAI::MovePiece(FMove& Move)
{
	if (!Move.ChessPiece) { UE_LOG(LogTemp, Warning, TEXT("Move.ChessPiece == nullptr!")) }
	if (!Move.PossibleTileToMove) { UE_LOG(LogTemp, Warning, TEXT("Move.PossibleTileToMove == nullptr!")) }

	if (Move.ChessPiece && Move.PossibleTileToMove)
	{
		Move.ChessPiece->MoveToNewTile(Move.PossibleTileToMove);
	}
		GameMode->ToggleTurn();
}

//FMove AChessAI::CalculateBestMove(ABoard*& Gameboard, FMove& Move, int depth)
//{
//	FMove MoveToReturn;
//	int BestValue = -9999;
//	int BoardValue = 0;
//
//	auto TempBoard = Gameboard->CreateTempGameBoard();
//	Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, TempBoard);
//
//	auto Moves = FindAllPossibleMoves(TempBoard);
//	for (auto& PossibleMove : Moves)
//	{
//		BoardValue = Minimax(TempBoard, PossibleMove, depth - 1);
//
//		if (BestValue < BestValue)
//		{
//			BestValue = BoardValue;
//			MoveToReturn = Move;
//			Move.Value = BoardValue;
//		}
//	}
//	TempBoard->DestroyBoard();
//	return MoveToReturn;
//}

FMove AChessAI::MiniMaxRoot(ABoard *& Gameboard, int depth, bool IsMaximisingPlayer)
{
	FMove BestMoveFound;
	int BestMove = -9999;

	auto PossibleMoves = FindAllPossibleMoves(Gameboard);

	for (auto& PossibleMove : PossibleMoves)
	{
		FMove Move;
		auto TempBoard = Gameboard->CreateTempGameBoard();

		for (auto& Piece : Gameboard->GetAllBlackPieces())
		{
			for (auto& tempPiece : TempBoard->GetAllBlackPieces())
			{
				if (Piece->GetCurrentTileName() == tempPiece->GetCurrentTileName())
				{
					Move.ChessPiece = tempPiece;
				}
			}
		}
		for (auto& Tile : Gameboard->GetAllTiles())
		{
			for (auto& tempTile : TempBoard->GetAllTiles())
			{
				if (tempTile->GetTileName() == tempTile->GetTileName())
				{
					Move.PossibleTileToMove = tempTile;
				}
			}
		}

		Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, TempBoard);
		int Value = Minimax(TempBoard, depth - 1, !IsMaximisingPlayer);
		UE_LOG(LogTemp, Warning, TEXT("Value in root: %i"), Value)
		if (Value >= BestMove)
		{
			BestMove = Value;
			BestMoveFound = PossibleMove;
		}
		PossibleMove.PossibleTileToMove->SetDefaultMaterial();
		TempBoard->DestroyBoard();
	}
	return BestMoveFound;
}

int AChessAI::Minimax(ABoard*& Gameboard, int depth, bool IsMaximisingPlayer)
{
	int ValueToReturn = 0;
	if (depth <= 0)
	{
		return -EvaluateBoard(Gameboard) + ValueToReturn;
	}
	auto TempBoard = Gameboard->CreateTempGameBoard();
	auto PossibleMoves = FindAllPossibleMoves(TempBoard);
	if (IsMaximisingPlayer)
	{
		int BestMove = 0;
		for (auto& PossibleMove : PossibleMoves)
		{
			PossibleMove.ChessPiece->AI_TestMove(PossibleMove.PossibleTileToMove, TempBoard);
			int Value = Minimax(TempBoard, depth - 1, !IsMaximisingPlayer);
			//if (Value > BestMove)
			//{
				ValueToReturn += Value;
			//}
		}
	}
	else
	{
		int BestMove = 0;
		for (auto& PossibleMove : PossibleMoves)
		{
			PossibleMove.ChessPiece->AI_TestMove(PossibleMove.PossibleTileToMove, TempBoard);
			int Value = Minimax(TempBoard, depth - 1, !IsMaximisingPlayer);
			//if (Value < BestMove)
			//{
				ValueToReturn -= Value;
			//}
		}
	}

	TempBoard->DestroyBoard();
	return ValueToReturn;
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

int AChessAI::EvaluateBoard(ABoard *& GameBoard)
{
	int Value = 0;

	for (auto& Piece : GameBoard->GetAllWhitePieces())
	{
		Value += Piece->GetMaterialValue();
	}

	for (auto& Piece : GameBoard->GetAllBlackPieces())
	{
		Value += Piece->GetMaterialValue();
	}

	return FMath::Abs(Value);
}
