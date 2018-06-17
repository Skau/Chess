// Fill out your copyright notice in the Description page of Project Settings.

#include "KingPiece.h"
#include "Tile.h"

TArray<ATile*>& AKingPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetTileUp())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileUp());
	}
	if (CurrentTile->GetTileDown())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileDown());
	}
	if (CurrentTile->GetTileLeft())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileLeft());
	}
	if (CurrentTile->GetTileRight())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileRight());
	}
	if (CurrentTile->GetTileDiagonalRightUp())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp());
	}
	if (CurrentTile->GetTileDiagonalRightDown())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown());
	}
	if (CurrentTile->GetTileDiagonalLeftUp())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp());
	}
	if (CurrentTile->GetTileDiagonalLeftDown())
	{
		PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown());
	}









	return PossibleTilesToMove;
}
