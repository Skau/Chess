// Fill out your copyright notice in the Description page of Project Settings.

#include "QueenPiece.h"
#include "Tile.h"
#include "Board.h"

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
	if (PossibleTilesToMove.Num())
	{
		PossibleTilesToMove.Empty();
	}

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }
	
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::UP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DOWN));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP));
	PossibleTilesToMove.Append(Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN));

	return PossibleTilesToMove;
}
