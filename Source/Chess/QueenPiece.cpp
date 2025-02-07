// Fill out your copyright notice in the Description page of Project Settings.

#include "QueenPiece.h"
#include "Tile.h"

void AQueenPiece::BeginPlay()
{
	Super::BeginPlay();

	if (GetIsWhite())
	{
		MaterialValue = 90;
	}
	else
	{
		MaterialValue = -90;
	}
}

TArray<ATile*>& AQueenPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

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
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTUP, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, Gameboard))
	{
		PossibleTilesToMove.Add(Tile);
	}

	return PossibleTilesToMove;
}
