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

TArray<ATile*>& ARookPiece::GetAllPossibleTiles(ABoard*& Gameboard, bool IsAI)
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::UP, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	} 
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DOWN, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::LEFT, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::RIGHT, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	return PossibleTilesToMove;
}
