// Fill out your copyright notice in the Description page of Project Settings.

#include "BishopPiece.h"
#include "Tile.h"
#include "Board.h"


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

TArray<ATile*>& ABishopPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	if (PossibleTilesToMove.Num())
	{
		PossibleTilesToMove.Empty();
	}

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN));

	return PossibleTilesToMove;
}
