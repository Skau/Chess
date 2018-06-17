// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightPiece.h"
#include "Tile.h"

TArray<ATile*>& AKnightPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetTileDiagonalRightUp())
	{
		if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
		}

		if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
		}
	}
	if (CurrentTile->GetTileDiagonalRightDown())
	{
		if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
		}

		if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
		}
	}
	if (CurrentTile->GetTileDiagonalLeftUp())
	{
		if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
		}

		if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
		}
	}
	if (CurrentTile->GetTileDiagonalLeftDown())
	{
		if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
		}

		if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown())
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
		}
	}

	return PossibleTilesToMove;
}
