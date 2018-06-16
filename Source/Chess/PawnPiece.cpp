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
	AllPossibleTiles.Empty();

	if (bIsWhite)
	{
		if (CurrentTile->GetTileLeft())
		{
			if (!CurrentTile->GetTileLeft()->GetHasChessPiece())
			{
				AllPossibleTiles.Add(CurrentTile->GetTileLeft());
			}

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
	else
	{
		if (CurrentTile->GetTileRight())
		{
			if (!CurrentTile->GetTileRight()->GetHasChessPiece())
			{
				AllPossibleTiles.Add(CurrentTile->GetTileRight());
			}

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

	if (bIsWhite)
	{
		// Diagonal Left
		if (CurrentTile->GetTileDiagonalLeftDown())
		{
			if (CurrentTile->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != bIsWhite)
				{
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
					CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					AllPossibleTiles.Add(CurrentTile->GetTileDiagonalRightDown());
				}
			}
		}
	}

	return AllPossibleTiles;
}
