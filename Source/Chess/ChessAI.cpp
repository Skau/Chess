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

void AChessAI::StartRound(ABoard *& GameBoard)
{
	//Calculate etc..
	FMove Move = MiniMaxRoot(GameBoard, 2, true);

	TArray<FMove> AllPossibleMoves = FindAllPossibleMoves(GameBoard, false);

	if (Move.ChessPiece)
	{
		UE_LOG(LogTemp, Warning, TEXT("Move.Value = %i"), Move.Value)
		if (Move.Value < AllPossibleMoves.Num())
		{
			MovePiece(AllPossibleMoves[Move.Value]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FINAL Move.ChessPiece == nullptr!"))
	}


	for (auto& Move : AllPossibleMoves)
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

	TArray<FMove> PossibleMoves = FindAllPossibleMoves(Gameboard, !IsMaximisingPlayer);
	
	for (int i = 0; i < PossibleMoves.Num(); ++i)
	{
		FMove Move;
		auto TempBoard = Gameboard->CreateTempGameBoard();
		AllTempBoards.Add(TempBoard);
		TArray<FMove> AllPossibleMoves = FindAllPossibleMoves(TempBoard, !IsMaximisingPlayer);
		UE_LOG(LogTemp, Warning, TEXT("ROOT: RootMoves.Num(): %i"), AllPossibleMoves.Num())
		Move = AllPossibleMoves[i];

		if (Move.ChessPiece)
		{
			UE_LOG(LogTemp, Warning, TEXT("ROOT: Move.Chesspiece is valid!"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ROOT: Move.Chesspiece is NOT valid!"))
		}

		Move.ChessPiece->AI_TestMove(Move.PossibleTileToMove, TempBoard);

		int Value = Minimax(TempBoard, depth - 1, -10000, 10000, !IsMaximisingPlayer);

		TempBoard->DestroyBoard();

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
	if (depth <= 0)
	{
		return -EvaluateBoard(Gameboard);
	}

	auto RootBoard = Gameboard->CreateTempGameBoard();
	AllTempBoards.Add(RootBoard);
	TArray<FMove> RootMoves = FindAllPossibleMoves(RootBoard, !IsMaximisingPlayer);
	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves.Num(): %i"), RootMoves.Num())
	if (IsMaximisingPlayer)
	{
		int BestMove = -9999;
		for (int i = 0; i < RootMoves.Num(); ++i)
		{
			auto TempBoard = Gameboard->CreateTempGameBoard();
			AllTempBoards.Add(TempBoard);
			TArray<FMove> PossibleMoves = FindAllPossibleMoves(TempBoard, !IsMaximisingPlayer);
			FMove Move;
			UE_LOG(LogTemp, Warning, TEXT("MINIMAX: IsMaximisingPlayer - i: %i"), i)

			Move = PossibleMoves[i];

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
			TArray<FMove> PossibleMoves = FindAllPossibleMoves(TempBoard, !IsMaximisingPlayer);
			FMove Move;
			UE_LOG(LogTemp, Warning, TEXT("!IsMaximisingPlayer - i: %i"), i)

			Move = PossibleMoves[i];

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

// TODO: Fix.. Returns empty in Minimax (also random crash when black captured white)
TArray<FMove> AChessAI::FindAllPossibleMoves(ABoard*& GameBoard, bool IsMaximisingPlayer)
{
	TArray<FMove> Moves;
	FMove NewMove;
	NewMove.ChessPiece = nullptr;
	NewMove.PossibleTileToMove = nullptr;

	if (IsMaximisingPlayer)
	{
		for (auto& Piece : GameBoard->GetAllWhitePieces())
		{
			for (auto& Tile : Piece->GetAllPossibleTiles())
			{
				Tile->SetIsPossibleMoveLocation(true);
				NewMove.ChessPiece = Piece;
				NewMove.PossibleTileToMove = Tile;
				Moves.Add(NewMove);
			}
		}
	}
	else
	{
		for (auto& Piece : GameBoard->GetAllBlackPieces())
		{
			for (auto& Tile : Piece->GetAllPossibleTiles())
			{
				Tile->SetIsPossibleMoveLocation(true);
				NewMove.ChessPiece = Piece;
				NewMove.PossibleTileToMove = Tile;
				Moves.Add(NewMove);
			}
		}
	}
	return Moves;
}

int AChessAI::EvaluateBoard(ABoard *& GameBoard)
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
