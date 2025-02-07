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
	auto Move = MiniMaxRoot(GameBoard, 4, 1);

	MovePiece(Move, GameBoard);
}

void AChessAI::MovePiece(FMove*& Move, ABoard*& Gameboard)
{
	if (!Move->ChessPiece) { UE_LOG(LogTemp, Error, TEXT("Move.ChessPiece == nullptr!")) }
	if (!Move->PossibleTileToMove) { UE_LOG(LogTemp, Error, TEXT("Move.PossibleTileToMove == nullptr!")) }
	if (!Gameboard) { UE_LOG(LogTemp, Error, TEXT("MovePiece: Gameboard arg in == nullptr!")) }

	if (Move->ChessPiece && Move->PossibleTileToMove && Gameboard)
	{
		Move->ChessPiece->MoveToNewTile(Move->PossibleTileToMove, Gameboard);
	}
	UE_LOG(LogTemp, Warning, TEXT("Total number of board evaluates: %i"), TotalNumberOfBoardEvaluates)
	TotalNumberOfBoardEvaluates = 0;

	if (PossibleTilesToMove.Num())
	{
		for (auto& Tile : PossibleTilesToMove)
		{
			Tile->PossibleTileToMove->SetIsPossibleCaptureLocation(false);

			Tile->PossibleTileToMove->SetIsPossibleMoveLocation(false);

			Tile->PossibleTileToMove->SetDefaultMaterial();
		}
		PossibleTilesToMove.Empty();
	}

	GameMode->ToggleTurn();
}

FMove* AChessAI::MiniMaxRoot(ABoard *& Gameboard, int depth, bool IsMaximisingPlayer)
{
	FMove* MoveToReturn = new FMove();
	int BestMove = -9999;
	SavedTiles.Empty();


	auto RootMoves = FindAllPossibleMoves(Gameboard, !IsMaximisingPlayer);

	UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves.Num(): %i"), RootMoves.Num())

	FString Color = "white";
	FString OtherColor = "black";
	if (!RootMoves[0]->ChessPiece->GetIsWhite())
	{
		Color = "black";
		OtherColor = "white";
	}
	UE_LOG(LogTemp, Warning, TEXT("AI_TestMove(MiniMaxRoot): %s %s on %s (Test tile: %s)"),
	*Color, *RootMoves[0]->ChessPiece->GetName(), *RootMoves[0]->ChessPiece->GetCurrentTile()->GetTileName().ToString(), *RootMoves[0]->PossibleTileToMove->GetTileName().ToString())
	
	RootMoves[0]->ChessPiece->AI_TestMove(RootMoves[0]->PossibleTileToMove, Gameboard); 
	
	int Value = Minimax(Gameboard, depth - 1, -10000, 10000, !IsMaximisingPlayer);
	
	
	Undo(RootMoves[0], Gameboard, true);
	
	return RootMoves[0];

	//for (int i = 0; i < RootMoves.Num(); ++i)
	//{
	//	FString Color = "white";
	//	FString OtherColor = "black";
	//	if (!RootMoves[i]->ChessPiece->GetIsWhite())
	//	{
	//		Color = "black";
	//		OtherColor = "white";
	//	}
	//	UE_LOG(LogTemp, Warning, TEXT("AI_TestMove(MiniMaxRoot): %s %s on %s (Test tile: %s)"),
	//		*Color, *RootMoves[i]->ChessPiece->GetName(), *RootMoves[i]->ChessPiece->GetCurrentTile()->GetTileName().ToString(), *RootMoves[i]->PossibleTileToMove->GetTileName().ToString())

	//	RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);
	//	
	//	int Value = Minimax(Gameboard, depth - 1, -10000, 10000, !IsMaximisingPlayer);

	//	if (i < RootMoves.Num() - 2)
	//	{
	//		Gameboard->RootUndo();
	//	}

	//	if (i == RootMoves.Num() - 2)
	//		Undo(RootMoves[i], Gameboard, true);
	//	else /*(i < RootMoves.Num() - 2)*/
	//		Undo(RootMoves[i], Gameboard, false);


	//	if (Value >/*=*/ BestMove)  
	//	{
	//		BestMove = Value;
	//		MoveToReturn = RootMoves[i];
	//		MoveToReturn->Value = i;
	//	}
	//}
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
		UE_LOG(LogTemp, Warning, TEXT("MINIMAX(%i): RootMoves.Num(): %i"), depth, RootMoves.Num())
		UE_LOG(LogTemp, Warning, TEXT("MINIMAXROOT: RootMoves.Num(): %i"), RootMoves.Num())
		FString Color = "white";
		FString OtherColor = "black";
		if (!RootMoves[0]->ChessPiece->GetIsWhite())
		{
			Color = "black";
			OtherColor = "white";
		}
		UE_LOG(LogTemp, Warning, TEXT("AI_TestMove(MINIMAX(%i): %s %s on %s (Test tile: %s)"),
		depth, *Color, *RootMoves[0]->ChessPiece->GetName(), *RootMoves[0]->ChessPiece->GetCurrentTile()->GetTileName().ToString(), *RootMoves[0]->PossibleTileToMove->GetTileName().ToString())
		
		RootMoves[0]->ChessPiece->AI_TestMove(RootMoves[0]->PossibleTileToMove, Gameboard);
		
		Minimax(Gameboard, depth - 1, Alpha, Beta, !IsMaximisingPlayer);
		
		Undo(RootMoves[0], Gameboard, false);
		return 0;

		/*if (IsMaximisingPlayer)
		{
			int BestMove = -9999;
			for (int i = 0; i < RootMoves.Num(); ++i)
			{
				FString Color = "white";
				FString OtherColor = "black";
				if (!RootMoves[i]->ChessPiece->GetIsWhite())
				{
					Color = "black";
					OtherColor = "white";
				}
				UE_LOG(LogTemp, Warning, TEXT("AI_TestMove(MINIMAX(%i): %s %s on %s (Test tile: %s)"),
					depth, *Color, *RootMoves[i]->ChessPiece->GetName(), *RootMoves[i]->ChessPiece->GetCurrentTile()->GetTileName().ToString(), *RootMoves[i]->PossibleTileToMove->GetTileName().ToString())
				RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);

				BestMove = FMath::Max(BestMove, Minimax(Gameboard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				if (i < RootMoves.Num() - 1)
					Undo(RootMoves[i], Gameboard, false);
				else if (i == RootMoves.Num()-1)
					Undo(RootMoves[i], Gameboard, true);

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
				FString Color = "white";
				FString OtherColor = "black";
				if (!RootMoves[i]->ChessPiece->GetIsWhite())
				{
					Color = "black";
					OtherColor = "white";
				}
				UE_LOG(LogTemp, Warning, TEXT("AI_TestMove(MINIMAX(%i): %s %s on %s (Test tile: %s)"),
					depth, *Color, *RootMoves[i]->ChessPiece->GetName(), *RootMoves[i]->ChessPiece->GetCurrentTile()->GetTileName().ToString(), *RootMoves[i]->PossibleTileToMove->GetTileName().ToString())
				RootMoves[i]->ChessPiece->AI_TestMove(RootMoves[i]->PossibleTileToMove, Gameboard);

				BestMove = FMath::Min(BestMove, Minimax(Gameboard, depth - 1, Alpha, Beta, !IsMaximisingPlayer));

				if (i < RootMoves.Num() - 1)
					Undo(RootMoves[i], Gameboard, false);
				else if (i == RootMoves.Num() - 1)
					Undo(RootMoves[i], Gameboard, true);

				Beta = FMath::Min(Beta, BestMove);
				if (Beta <= Alpha)
				{
					return BestMove;
				}

			}
			return BestMove;
		}*/
	}
	return 0;
}

TArray<FMove*>& AChessAI::FindAllPossibleMoves(ABoard*& GameBoard, bool IsMaximisingPlayer)
{
	if (PossibleTilesToMove.Num())
	{
		PossibleTilesToMove.Empty();
	}

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
							if (Tile->GetChessPiece() != RootTiles->GetChessPiece())
							{
								if (!Tile->GetChessPiece()->GetIsWhite())
								{
									Tile->SetIsPossibleMoveLocation(true);
									Tile->SetIsPossibleCaptureLocation(true);
								}
							}
							else
							{
								Tile->SetIsPossibleMoveLocation(true);

							}
						}
						PossibleTilesToMove.Add(new FMove(RootTiles->GetChessPiece(), Tile, index));
					}
				}
			}
		}
	}
	else
	{
		int index = 0;
		// For all tiles
		for (auto& RootTiles : GameBoard->GetAllTiles())
		{
			// If the tile has a chess piece
			if (RootTiles->GetHasChessPiece())
			{
				// If the piece is black
				if (!RootTiles->GetChessPiece()->GetIsWhite())
				{
					// For each tile in that are possible to move to
					for (auto& Tile : RootTiles->GetChessPiece()->GetAllPossibleTiles(GameBoard))
					{
						if (Tile->GetHasChessPiece())
						{
							if (Tile->GetChessPiece() != RootTiles->GetChessPiece())
							{
								if (Tile->GetChessPiece()->GetIsWhite())
								{
									Tile->SetIsPossibleMoveLocation(true);
									Tile->SetIsPossibleCaptureLocation(true);
								}
							}

						}
						else
						{
							Tile->SetIsPossibleMoveLocation(true);
						}
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

void AChessAI::Undo(FMove*& Move, ABoard*& Gameboard, bool IsLastRegularUndo)
{
	UE_LOG(LogTemp, Warning, TEXT("Regular undo"))
	if (Gameboard)
	{
		for (auto& Tile : Gameboard->GetAllTiles())
		{
			// Resets bIsFirstMove if simulated
			if (Tile->GetChessPiece())
			{
				if (Tile->GetChessPiece()->GetHasFirstTempMoved() && Tile->GetChessPiece()->GetHasFirstMoved())
				{
					Tile->GetChessPiece()->ResetHasTempFirstMoved();
				}
			}
			// Resets board to last moves before simulating.
			//Tile->ResetTileToLastState();
		}

		if (Move)
		{
			Move->ChessPiece->AI_UndoTestMove(Move, Gameboard, IsLastRegularUndo);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("RegularUndo: Move is NOT valid!"))
		}
	} 
}
