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

TArray<ATile*>& ABishopPiece::GetAllPossibleTiles(ABoard*& Gameboard, bool IsAI)
{
	PossibleTilesToMove.Empty();
	
	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTUP, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	for (auto& Tile : CurrentTile->GetAllTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, Gameboard, IsAI))
	{
		PossibleTilesToMove.Add(Tile);
	}
	return PossibleTilesToMove;
}
