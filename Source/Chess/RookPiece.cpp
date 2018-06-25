// Fill out your copyright notice in the Description page of Project Settings.

#include "RookPiece.h"
#include "Tile.h"

void ARookPiece::BeginPlay()
{
	Super::BeginPlay();

	if (GetIsWhite())
	{
		MaterialValue = 50;
	}
	else
	{
		MaterialValue = -50;
	}
}

TArray<ATile*>& ARookPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	PossibleTilesToMove.Empty();

	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::UP, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	} 
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DOWN, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::LEFT, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::RIGHT, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	return PossibleTilesToMove;
}
