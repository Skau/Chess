// Fill out your copyright notice in the Description page of Project Settings.

#include "RookPiece.h"
#include "Tile.h"
#include "Board.h"

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
	if (PossibleTilesToMove.Num())
	{
		PossibleTilesToMove.Empty();
	}

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::UP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DOWN));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT));

	return PossibleTilesToMove;
}
