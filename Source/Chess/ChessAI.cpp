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
	auto Move = MiniMaxRoot(GameBoard, 2, true);

	//if (Move->ChessPiece)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FINAL Move.ChessPiece is valid"))
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FINAL Move.ChessPiece == nullptr!"))
	//}
	
	MovePiece(Move, GameBoard);

}

void AChessAI::MovePiece(FMove*& Move, ABoard*& Gameboard)
{
	if (!Move->ChessPiece) { UE_LOG(LogTemp, Warning, TEXT("Move.ChessPiece == nullptr!")) }
	if (!Move->PossibleTileToMove) { UE_LOG(LogTemp, Warning, TEXT("Move.PossibleTileToMove == nullptr!")) }

	if (Move->ChessPiece && Move->PossibleTileToMove)
	{
		Move->ChessPiece->MoveToNewTile(Move->PossibleTileToMove);
	}
	UE_LOG(LogTemp, Warning, TEXT("Total number of board evaluates: %i"), TotalNumberOfBoardEvaluates)
	TotalNumberOfBoardEvaluates = 0;

	// TODO: 1. CurrentChessPiece in Tile won't update on "real" move for AI. 
	// TODO: 2. Cannot capture pieces (crash)
	// Probably more...

	for (auto& Tile : Gameboard->GetAllTiles())
	{
		Tile->SetCurrentChessPieceToNull();
		Tile->SetDefaultMaterial();
		Tile->ResetToRootChessPiece();
		if (Tile->GetHasChessPiece())
		{
			Tile->GetChessPiece()->SetCurrentTileToRootTile();
		}
	}

	//if (PossibleTilesToMove.Num())
	//{
	//	for (auto& Tile : PossibleTilesToMove)
	//	{
	//		Tile->PossibleTileToMove->SetIsPossibleCaptureLocation(false);

	//		Tile->PossibleTileToMove->SetIsPossibleMoveLocation(false);

	//		Tile->PossibleTileToMove->SetDefaultMaterial();
	//	}
	//	PossibleTilesToMove.Empty();
	//}

	GameMode->ToggleTurn();
}

FMove* AChessAI::MiniMaxRoot(ABoard *& Gameboard, int depth, bool IsMaximisingPlayer)
{
	FMove* MoveToReturn = new FMove();
	int BestMove = -9999;
	SavedTiles.Empty();

	Gameboard->SaveCurrentChessPieces(true);

	auto RootMoves = FindAllPossibleMoves(Gameboard, !IsMaximisingPlayer);
	UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves.Num(): %i"), RootMoves.Num())
	for (int i = 0; i < RootMoves.Num(); ++i)
	{

		//if (RootMoves[i]->ChessPiece)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves[i]->Chesspiece is valid!"))
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves[i]->Chesspiece is NOT valid!"))
		//}

		RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);

		int Value = Minimax(Gameboard, depth - 1, -10000, 10000, !IsMaximisingPlayer);

		Undo(Gameboard);

		if (Value > BestMove)
		{
			BestMove = Value;
			MoveToReturn = RootMoves[i];
			MoveToReturn->Value = i;
		}
	}
	return MoveToReturn;
}

int AChessAI::Minimax(ABoard*& Gameboard, int depth, int Alpha, int Beta, bool IsMaximisingPlayer)
{
	if (depth == 0)
	{
		return -EvaluateBoard(Gameboard);
	}

	TArray<FMove*> RootMoves = FindAllPossibleMoves(Gameboard, !IsMaximisingPlayer);

	if (RootMoves.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves.Num(): %i"), RootMoves.Num())
		if (IsMaximisingPlayer)
		{
			int BestMove = -9999;
			for (int i = 0; i < RootMoves.Num(); ++i)
			{
				//UE_LOG(LogTemp, Warning, TEXT("MINIMAX: IsMaximisingPlayer - i: %i"), i)

				//if (RootMoves[i]->ChessPiece)
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves[i]->Chesspiece is valid!"))
				//}
				//else
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves[i]->Chesspiece is NOT valid!"))
				//}

				RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);

				BestMove = FMath::Max(BestMove, Minimax(Gameboard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				Undo(Gameboard);

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
				//UE_LOG(LogTemp, Warning, TEXT("!IsMaximisingPlayer - i: %i"), i)

				//if (RootMoves[i]->ChessPiece)
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves[i]->Chesspiece is valid!"))
				//}
				//else
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves[i]->Chesspiece is NOT valid!"))
				//}

				RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);

				BestMove = FMath::Min(BestMove, Minimax(Gameboard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				Undo(Gameboard);

				Beta = FMath::Min(Beta, BestMove);
				if (Beta <= Alpha)
				{
					return BestMove;
				}

			}
			return BestMove;
		}
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("MINIMAX: RootMoves.Num() == 0!"))
	//}
	return 0;
}

TArray<FMove*>& AChessAI::FindAllPossibleMoves(ABoard*& GameBoard, bool IsMaximisingPlayer)
{
	//if (PossibleTilesToMove.Num())
	//{
	//	for (auto& Tile : PossibleTilesToMove)
	//	{
	//		Tile->PossibleTileToMove->SetIsPossibleCaptureLocation(false);

	//		Tile->PossibleTileToMove->SetIsPossibleMoveLocation(false);

	//		Tile->PossibleTileToMove->SetDefaultMaterial();
	//	}
	//	PossibleTilesToMove.Empty();
	//}

	PossibleTilesToMove.Empty();

	if (IsMaximisingPlayer)
	{
		int index = 0;
		for (auto& RootTiles : GameBoard->GetAllTiles())
		{
			if (RootTiles->GetHasChessPiece())
			{
				if (RootTiles->GetChessPiece()->GetIsWhite())
				{
					for (auto& Tile : RootTiles->GetChessPiece()->GetAllPossibleTiles(GameBoard))
					{
						if (Tile->GetHasChessPiece())
						{
							if (!Tile->GetChessPiece()->GetIsWhite())
							{
								Tile->SetIsPossibleCaptureLocation(true);
							}
						}
						Tile->SetIsPossibleMoveLocation(true);
						PossibleTilesToMove.Add(new FMove(RootTiles->GetChessPiece(), Tile, index));
					}
				}
			}
		}
	}
	else
	{
		int index = 0;
		for (auto& RootTiles : GameBoard->GetAllTiles())
		{
			if (RootTiles->GetHasChessPiece())
			{
				if (!RootTiles->GetChessPiece()->GetIsWhite())
				{
					for (auto& Tile : RootTiles->GetChessPiece()->GetAllPossibleTiles(GameBoard))
					{
						if (Tile->GetHasChessPiece())
						{
							if (Tile->GetChessPiece()->GetIsWhite())
							{
								Tile->SetIsPossibleCaptureLocation(true);
							}
						}
						Tile->SetIsPossibleMoveLocation(true);
						PossibleTilesToMove.Add(new FMove(RootTiles->GetChessPiece(), Tile, index));
					}
				}
			}
		}
	}
	return PossibleTilesToMove;
}

int AChessAI::EvaluateBoard(ABoard*& GameBoard)
{
	TotalNumberOfBoardEvaluates++;
	int Value = 0;

	for (auto& Tile : GameBoard->GetAllTiles())
	{
		if (Tile->GetHasChessPiece())
		{ 
			Tile->GetChessPiece()->GetIsWhite() ?
			Value += Tile->GetChessPiece()->GetMaterialValue() : 
			Value -= Tile->GetChessPiece()->GetMaterialValue() ;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("EvaluateBoard: %i"), Value)
	return Value;
}

void AChessAI::Undo(ABoard*& Gameboard)
{
	if (Gameboard)
	{
		// If has tempmoved, set to current and null currentchesspiece
		Gameboard->ResetAllChessPiecesToCurrentState();
	} 
}
