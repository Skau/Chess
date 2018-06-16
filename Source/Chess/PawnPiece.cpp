// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnPiece.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameModeBase.h"
#include "Board.h"
#include "Tile.h"

APawnPiece::APawnPiece()
{
	
}

void APawnPiece::BeginPlay()
{
	Super::BeginPlay();
}

void APawnPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<ATile*>& APawnPiece::GetAllPossibleTiles()
{
	GameMode = Cast<AChessGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameBoard = GameMode->GetGameBoard();

	AllPossibleTiles.Empty();

	TArray<ATile*> AllTiles;
	if (GameBoard)
	{
		AllTiles = GameBoard->GetAllTiles();
	}
	int index = 0;

	for (auto& Tile : AllTiles)
	{
		if (GetCurrentTile() == Tile)
		{
			int MaxSearch= 0;
			if (bIsFirstMove)
			{
				MaxSearch = 2;
			}
			else
			{
				MaxSearch = 1;
			}
			for (int i = 0; i <= MaxSearch; ++i)
			{
				// UP
				//if (index - i >= 0 && index - i <= 63)
				//{
				//	if (!AllTiles[index - i]->GetHasChessPiece())
				//	{
				//		AllPossibleTiles.Add(AllTiles[index - i]);
				//		UE_LOG(LogTemp, Warning, TEXT("UP: index(%i) - i(%i) = %i"), index, i, index - i)
				//	}
				//	else
				//	{
				//		UE_LOG(LogTemp, Warning, TEXT("UP: Cannot move here because tile %i is taken"), index - i)
				//	}
				//}

				// DOWN
				//if (index + i >= 0 && index + i <= 63)
				//{
				//	if (!AllTiles[index + i]->GetHasChessPiece())
				//	{
				//		AllPossibleTiles.Add(AllTiles[index + i]);
				//		UE_LOG(LogTemp, Warning, TEXT("DOWN: index(%i) + i(%i) = %i"), index, i, index + i)
				//	}
				//	else
				//	{
				//		UE_LOG(LogTemp, Warning, TEXT("DOWN: Cannot move here because tile %i is taken"), index + i)
				//	}
				//}

				if (bIsWhite)
				{
					// LEFT
					if (index + 8 * i >= 0 && index + 8 * i <= 63)
					{
						if (!AllTiles[index + 8 * i]->GetHasChessPiece())
						{
							AllPossibleTiles.Add(AllTiles[index + 8 * i]);
							//UE_LOG(LogTemp, Warning, TEXT("LEFT: index(%i) + 8 * i(%i) = %i"), index, i, index + 8 * i)
						}
						else
						{
							//UE_LOG(LogTemp, Warning, TEXT("LEFT: Cannot move here because tile %i is taken"), (index + 8 * i))
						}
					}
				}
				else
				{
					// RIGHT
					if (index - 8 * i >= 0 && index - 8 * i <= 63)
					{
						if (!AllTiles[index - 8 * i]->GetHasChessPiece())
						{
							AllPossibleTiles.Add(AllTiles[index - 8 * i]);
							//UE_LOG(LogTemp, Warning, TEXT("RIGHT: index(%i) - 8 * i(%i) = %i"), index, i, index - 8 * i)
						}
						else
						{
							//UE_LOG(LogTemp, Warning, TEXT("RIGHT: Cannot move here because tile %i is taken"), (index - 8 * i))
						}
					}
				}
			}
			break;
		}
		index++;
	}

	if (bIsWhite)
	{
		// Diagonal Left
		if (index + 7>= 0 && index + 7 <= 63)
		{
			if (AllTiles[index + 7]->GetHasChessPiece())
			{
				if (AllTiles[index + 7]->GetChessPiece()->GetIsWhite() != bIsWhite)
				{
					AllTiles[index + 7]->SetIsPossibleCaptureLocation(true);
					AllPossibleTiles.Add(AllTiles[index + 7]);
					//UE_LOG(LogTemp, Warning, TEXT("DIAGONAL LEFT: index(%i) + 7 = %i"), index, index + 7)
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("LEFT: Cannot move here because tile %i is not taken"), (index + 7))
			}
		}
		// Diagonal Right
		if (index + 9 >= 0 && index + 9 <= 63)
		{
			if (AllTiles[index + 9]->GetHasChessPiece())
			{
				if (AllTiles[index + 9]->GetChessPiece()->GetIsWhite() != bIsWhite)
				{
					AllTiles[index + 9]->SetIsPossibleCaptureLocation(true);
					AllPossibleTiles.Add(AllTiles[index + 9]);
					//UE_LOG(LogTemp, Warning, TEXT("DIAGONAL LEFT: index(%i) + 9 = %i"), index, index + 9)
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("LEFT: Cannot move here because tile %i is not taken"), (index + 9))
			}
		}
	}
	else
	{
		// Diagonal Left
		if (index - 9 >= 0 && index - 9 <= 63)
		{
			if (AllTiles[index - 9]->GetHasChessPiece())
			{
				if (AllTiles[index - 9]->GetChessPiece()->GetIsWhite() != bIsWhite)
				{
					AllTiles[index - 9]->SetIsPossibleCaptureLocation(true);
					AllPossibleTiles.Add(AllTiles[index - 9]);
					//UE_LOG(LogTemp, Warning, TEXT("DIAGONAL LEFT: index(%i) - 9 = %i"), index, index - 9)
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("DIAGONAL LEFT: Cannot move here because tile %i is not taken"), (index - 9))
			}
		}
		// Diagonal Right
		if (index - 7 >= 0 && index - 7 <= 63)
		{
			if (AllTiles[index - 7]->GetHasChessPiece())
			{
				if (AllTiles[index - 7]->GetChessPiece()->GetIsWhite() != bIsWhite)
				{
					AllTiles[index - 7]->SetIsPossibleCaptureLocation(true);
					AllPossibleTiles.Add(AllTiles[index - 7]);
					//UE_LOG(LogTemp, Warning, TEXT("DIAGONAL RIGHT: index(%i) - 7 = %i"), index, index - 7)
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("LEFT: Cannot move here because tile %i is not taken"), (index - 7))
			}
		}
	}

	return AllPossibleTiles;
}
