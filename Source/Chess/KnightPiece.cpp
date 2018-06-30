// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightPiece.h"
#include "Tile.h"
#include "Board.h"

void AKnightPiece::BeginPlay()
{
	Super::BeginPlay();

	if (GetIsWhite())
	{
		MaterialValue = 30;
	}
	else
	{
		MaterialValue = -30;
	}
}

TArray<ATile*>& AKnightPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }
	
	if (CurrentTile->GetTileDiagonalRightUp())
	{
		ATile*& Tile = CurrentTile->GetTileDiagonalRightUp();
		if (Gameboard->GetTilesInADirection(Tile, EDirection::UP, true, 1).IsValidIndex(1))
		{
			PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::UP, true, 1)[1]);
		}
		if (Gameboard->GetTilesInADirection(Tile, EDirection::RIGHT, true, 1).IsValidIndex(1))
		{
			PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::RIGHT, true, 1)[1]);
		}
	}

	if (CurrentTile->GetTileDiagonalRightDown())
	{
		ATile*& Tile = CurrentTile->GetTileDiagonalRightDown();
		if (Gameboard->GetTilesInADirection(Tile, EDirection::RIGHT, true, 1).IsValidIndex(1))
		{
			PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::RIGHT, true, 1)[1]);
		}

		if (Gameboard->GetTilesInADirection(Tile, EDirection::DOWN, true, 1).IsValidIndex(1))
		{
			PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DOWN, true, 1)[1]);
		}
	}


	if (CurrentTile->GetTileDiagonalLeftUp())
	{
		ATile*& Tile = CurrentTile->GetTileDiagonalLeftUp();
		if (Tile)
		{
			if (Gameboard->GetTilesInADirection(Tile, EDirection::LEFT, true, 1).IsValidIndex(1))
			{
				PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::LEFT, true, 1)[1]);
			}

			if (Gameboard->GetTilesInADirection(Tile, EDirection::UP, true, 1).IsValidIndex(1))
			{
				PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::UP, true, 1)[1]);
			}
		}
	}



	if (CurrentTile->GetTileDiagonalLeftDown())
	{
		ATile*& Tile = CurrentTile->GetTileDiagonalLeftDown();
		if (Tile)
		{
			if (Gameboard->GetTilesInADirection(Tile, EDirection::LEFT, true, 1).IsValidIndex(1))
			{
				PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::LEFT, true, 1)[1]);
			}

			if (Gameboard->GetTilesInADirection(Tile, EDirection::DOWN, true, 1).IsValidIndex(1))
			{
				PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DOWN, true, 1)[1]);
			}
		}
	}

	return PossibleTilesToMove;
}
