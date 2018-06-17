// Fill out your copyright notice in the Description page of Project Settings.

#include "RookPiece.h"
#include "Tile.h"
TArray<ATile*>& ARookPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::UP))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DOWN))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::LEFT))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::RIGHT))
	{
		PossibleTilesToMove.Add(Tile);
	}
	return PossibleTilesToMove;
}
