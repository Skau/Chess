// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessAI.h"
#include "Templates/SharedPointer.h"
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

void AChessAI::StartRound(ABoard*& GameBoard)
{
	FMove Move = MiniMaxRoot(GameBoard, 1, true);
	FindAllPossibleMoves(GameBoard,  false);

	if (Move.ChessPiece)
	{
		UE_LOG(LogTemp, Warning, TEXT("Move.Value = %i"), Move.Value)
		if (Move.Value < PossibleTilesToMove.Num())
		{
			MovePiece(PossibleTilesToMove[Move.Value]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FINAL Move.ChessPiece == nullptr!"))
	}


	for (auto& Move : PossibleTilesToMove)
	{
		if (Move.PossibleTileToMove)
		{
			Move.PossibleTileToMove->SetDefaultMaterial();
		}
	}
}

void AChessAI::MovePiece(FMove& Move)
{
	if (!Move.ChessPiece) { UE_LOG(LogTemp, Warning, TEXT("Move.ChessPiece == nullptr!")) }
	if (!Move.PossibleTileToMove) { UE_LOG(LogTemp, Warning, TEXT("Move.PossibleTileToMove == nullptr!")) }

	if (Move.ChessPiece && Move.PossibleTileToMove)
	{
		Move.ChessPiece->MoveToNewTile(Move.PossibleTileToMove);
	}
	UE_LOG(LogTemp, Warning, TEXT("Total number of board evaluates: %i"), TotalNumberOfBoardEvaluates)
	TotalNumberOfBoardEvaluates = 0;

	for (auto& Board : AllTempBoards)
	{
		Board->DestroyBoard();
	}
	AllTempBoards.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Total number of boards left: %i"), AllTempBoards.Num())

	GameMode->ToggleTurn();
}

FMove AChessAI::MiniMaxRoot(ABoard *& Gameboard, int depth, bool IsMaximisingPlayer)
{
	FMove BestMoveFound;
	int BestMove = -9999;
	auto Board = Gameboard->CreateTempGameBoard();
	AllTempBoards.Add(Board);
	auto RootMoves = FindAllPossibleMoves(Board, !IsMaximisingPlayer);
	UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves.Num(): %i"), RootMoves.Num())
	for (int i = 0; i < RootMoves.Num(); ++i)
	{
		if (!Board)
		{
			Board = Gameboard->CreateTempGameBoard();
		}

		FMove Move;
		Move = RootMoves[i];

		if (Move.ChessPiece)
		{
			UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: Move.Chesspiece is valid!"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: Move.Chesspiece is NOT valid!"))
		}

		Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, Board);
		int Value = Minimax(Board, depth - 1, -10000, 10000, !IsMaximisingPlayer);

		Board->DestroyBoard();

		if (Value > BestMove)
		{
			BestMove = Value;
			BestMoveFound = Move;
			BestMoveFound.Value = i;
		}
	}
	return BestMoveFound;
}

int AChessAI::Minimax(ABoard*& Gameboard, int depth, int Alpha, int Beta, bool IsMaximisingPlayer)
{
	if (depth == 0)
	{
		return -EvaluateBoard(Gameboard);
	}

	auto RootBoard = Gameboard->CreateTempGameBoard();
	AllTempBoards.Add(RootBoard);
	TArray<FMove>& RootMoves = FindAllPossibleMoves(RootBoard, !IsMaximisingPlayer);

	if (RootMoves.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves.Num(): %i"), RootMoves.Num())
		if (IsMaximisingPlayer)
		{
			int BestMove = -9999;
			for (int i = 0; i < RootMoves.Num(); ++i)
			{
				auto TempBoard = Gameboard->CreateTempGameBoard();
				AllTempBoards.Add(TempBoard);
				auto Moves = FindAllPossibleMoves(TempBoard, !IsMaximisingPlayer);
				FMove Move;
				UE_LOG(LogTemp, Warning, TEXT("MINIMAX: IsMaximisingPlayer - i: %i"), i)
				Move = Moves[i];

				if (Move.ChessPiece)
				{
					UE_LOG(LogTemp, Warning, TEXT("MINIMAX: Move.Chesspiece is valid!"))
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MINIMAX: Move.Chesspiece is NOT valid!"))
				}

				Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, TempBoard);

				BestMove = FMath::Max(BestMove, Minimax(TempBoard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				TempBoard->DestroyBoard();

				Alpha = FMath::Max(Alpha, BestMove);
				if (Beta <= Alpha)
				{
					return BestMove;
				}
			}
			return BestMove;
		}
		else
		{
			int BestMove = 9999;
			for (int i = 0; i < RootMoves.Num(); ++i)
			{
				auto TempBoard = Gameboard->CreateTempGameBoard();
				AllTempBoards.Add(TempBoard);
				auto Moves = FindAllPossibleMoves(TempBoard, !IsMaximisingPlayer);
				FMove Move;
				UE_LOG(LogTemp, Warning, TEXT("!IsMaximisingPlayer - i: %i"), i)
					if (i < Moves.Num())
						Move = Moves[i];

				if (Move.ChessPiece)
				{
					UE_LOG(LogTemp, Warning, TEXT("MINIMAX: Move.Chesspiece is valid!"))
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("MINIMAX: Move.Chesspiece is NOT valid!"))
				}

				Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, TempBoard);

				BestMove = FMath::Min(BestMove, Minimax(TempBoard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				TempBoard->DestroyBoard();

				Beta = FMath::Min(Beta, BestMove);
				if (Beta <= Alpha)
				{
					return BestMove;
				}

			}
			return BestMove;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves.Num() == 0!"))
	}
	return 0;
}

TArray<FMove>& AChessAI::FindAllPossibleMoves(ABoard*& GameBoard, bool IsMaximisingPlayer)
{
	PossibleTilesToMove.Empty();

	FMove NewMove;
	NewMove.ChessPiece = nullptr;
	NewMove.PossibleTileToMove = nullptr;

	if (IsMaximisingPlayer)
	{
		for (auto& Piece : GameBoard->GetAllWhitePieces())
		{
			int index = 0;
			for (auto& Tile : Piece->GetAllPossibleTiles())
			{
				Tile->SetIsPossibleMoveLocation(true);
				NewMove.ChessPiece = Piece;
				NewMove.PossibleTileToMove = Tile;
				NewMove.Value = index;
				PossibleTilesToMove.Add(NewMove);
				index++;
			}
		}
	}
	else
	{
		for (auto& Piece : GameBoard->GetAllBlackPieces())
		{
			int index = 0;
			for (auto& Tile : Piece->GetAllPossibleTiles())
			{
				Tile->SetIsPossibleMoveLocation(true);
				NewMove.ChessPiece = Piece;
				NewMove.PossibleTileToMove = Tile;
				NewMove.Value = index;
				PossibleTilesToMove.Add(NewMove);
				index++;
			}
		}
	}
	return PossibleTilesToMove;
}

int AChessAI::EvaluateBoard(ABoard*& GameBoard)
{
	TotalNumberOfBoardEvaluates++;
	int Value = 0;

	for (auto& Piece : GameBoard->GetAllWhitePieces())
	{
		Value += Piece->GetMaterialValue();
		for (auto& Tile : Piece->GetAllPossibleTiles())
		{
			if (Tile->GetIsPossibleCaptureLocation())
			{
				Value += Tile->GetChessPiece()->GetMaterialValue();
			}
		}
	}

	for (auto& Piece : GameBoard->GetAllBlackPieces())
	{
		Value -= Piece->GetMaterialValue();
		for (auto& Tile : Piece->GetAllPossibleTiles())
		{
			if (Tile->GetIsPossibleCaptureLocation())
			{
				Value -= Tile->GetChessPiece()->GetMaterialValue();
			}
		}
		 
	}
	UE_LOG(LogTemp, Warning, TEXT("EvaluateBoard: %i"), Value)
	return Value;
}
