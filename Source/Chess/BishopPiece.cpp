// Fill out your copyright notice in the Description page of Project Settings.

#include "BishopPiece.h"
#include "Tile.h"


void ABishopPiece::BeginPlay()
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

TArray<ATile*>& ABishopPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTUP))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTUP))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN))
	{
		PossibleTilesToMove.Add(Tile);
	}
	return PossibleTilesToMove;
}
