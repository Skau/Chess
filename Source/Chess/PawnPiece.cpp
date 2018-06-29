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

	if (GetIsWhite())
	{
		MaterialValue = 10;
	}
	else
	{
		MaterialValue = -10;
	}
}

void APawnPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<ATile*>& APawnPiece::GetAllPossibleTiles(ABoard*& GameBoard, bool IsAI)
{
	UE_LOG(LogTemp, Warning, TEXT("AllPossibleTiles.Empty()"))
	AllPossibleTiles.Empty();

	// AI
	if (IsAI)
	{
		UE_LOG(LogTemp, Warning, TEXT("IsAI"))
		if (CurrentTile->GetLastSavedInfo()->ChessPiece == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetLastSavedInfo()->ChessPiece NULL ERROR")) return AllPossibleTiles; }
		else { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetLastSavedInfo()->ChessPiece was not nullptr")) }
		if (bIsWhite)
		{
			if (CurrentTile->GetTileLeft())
			{
				if (!CurrentTile->GetTileLeft()->GetLastSavedInfo()->ChessPiece)
				{
					AllPossibleTiles.Add(CurrentTile->GetTileLeft());

					if (bIsFirstMove)
					{
						if (CurrentTile->GetTileLeft()->GetTileLeft())
						{
							if (!CurrentTile->GetTileLeft()->GetTileLeft()->GetLastSavedInfo()->ChessPiece)
							{
								AllPossibleTiles.Add(CurrentTile->GetTileLeft()->GetTileLeft());
							}
						}
					}
				}
			}
		}
		else
		{
			if (CurrentTile->GetTileRight())
			{
				if (!CurrentTile->GetTileRight()->GetLastSavedInfo()->ChessPiece)
				{
					AllPossibleTiles.Add(CurrentTile->GetTileRight());

					if (bIsFirstMove)
					{
						if (CurrentTile->GetTileRight()->GetTileRight())
						{
							if (!CurrentTile->GetTileRight()->GetTileRight()->GetLastSavedInfo()->ChessPiece)
							{
								AllPossibleTiles.Add(CurrentTile->GetTileRight()->GetTileRight());
							}
						}
					}
				}
			}
		}

		if (bIsWhite)
		{
			// Diagonal Left
			if (CurrentTile->GetTileDiagonalLeftDown())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftDown()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalLeftDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalLeftDown());
					}
				}
			}
			// Diagonal Right
			if (CurrentTile->GetTileDiagonalLeftUp())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftUp()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalLeftUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalLeftUp());
					}
				}
			}
		}
		else
		{
			// Diagonal Left
			if (CurrentTile->GetTileDiagonalRightUp())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalRightUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalRightUp());
					}
				}
			}
			// Diagonal Right
			if (CurrentTile->GetTileDiagonalRightDown())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightDown()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalRightDown());
					}
				}
			}
		}
	}
	// Player
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IsPlayer"))
		if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return AllPossibleTiles; }
		else { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() is not NULL")) }
		if (bIsWhite)
		{
			if (CurrentTile->GetTileLeft())
			{
				if (!CurrentTile->GetTileLeft()->GetHasChessPiece())
				{
					AllPossibleTiles.Add(CurrentTile->GetTileLeft());

					if (bIsFirstMove)
					{
						if (CurrentTile->GetTileLeft()->GetTileLeft())
						{
							if (!CurrentTile->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
							{
								AllPossibleTiles.Add(CurrentTile->GetTileLeft()->GetTileLeft());
							}
						}
					}
				}
			}
		}
		else
		{
			if (CurrentTile->GetTileRight())
			{
				if (!CurrentTile->GetTileRight()->GetHasChessPiece())
				{
					AllPossibleTiles.Add(CurrentTile->GetTileRight());

					if (bIsFirstMove)
					{
						if (CurrentTile->GetTileRight()->GetTileRight())
						{
							if (!CurrentTile->GetTileRight()->GetTileRight()->GetHasChessPiece())
							{
								AllPossibleTiles.Add(CurrentTile->GetTileRight()->GetTileRight());
							}
						}
					}
				}
			}
		}

		if (bIsWhite)
		{
			// Diagonal Left
			if (CurrentTile->GetTileDiagonalLeftDown())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalLeftDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalLeftDown());
					}
				}
			}
			// Diagonal Right
			if (CurrentTile->GetTileDiagonalLeftUp())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalLeftUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalLeftUp());
					}
				}
			}
		}
		else
		{
			// Diagonal Left
			if (CurrentTile->GetTileDiagonalRightUp())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalRightUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalRightUp());
					}
				}
			}
			// Diagonal Right
			if (CurrentTile->GetTileDiagonalRightDown())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != bIsWhite)
					{
						CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
						AllPossibleTiles.Add(CurrentTile->GetTileDiagonalRightDown());
					}
				}
			}
		}
	}
	return AllPossibleTiles;
}
