// Fill out your copyright notice in the Description page of Project Settings.

#include "KingPiece.h"
#include "Tile.h"
#include "Board.h"

void AKingPiece::BeginPlay()
{
	Super::BeginPlay();

	if (GetIsWhite())
	{
		MaterialValue = 900;
	}
	else
	{
		MaterialValue = -900;
	}
}

TArray<ATile*>& AKingPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }


	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::UP, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::UP, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DOWN, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DOWN, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP, true, 1)[1]);
	}
	if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, 1).IsValidIndex(1))
	{
		PossibleTilesToMove.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, true, 1)[1]);
	}

	return PossibleTilesToMove;
}
