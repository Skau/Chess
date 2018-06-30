// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnPiece.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameModeBase.h"
#include "Board.h"
#include "Tile.h"

APawnPiece::APawnPiece()
{
	
}

void APawnPiece::BeginPlay()
{
	Super::BeginPlay();

	if (GetIsWhite())
	{
		MaterialValue = 10;
	}
	else
	{
		MaterialValue = -10;
	}
}

void APawnPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<ATile*>& APawnPiece::GetAllPossibleTiles(ABoard*& Gameboard)
{
	AllPossibleTiles.Empty();

	if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return AllPossibleTiles; }

	if (bIsWhite)
	{
		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, false, 1).IsValidIndex(1))
		{
			AllPossibleTiles.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, false, 1)[1]);

			if (bIsFirstMove)
			{
				if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, false, 2).IsValidIndex(2))
				{
					AllPossibleTiles.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::LEFT, false, 2)[2]);
				}
			}
		
		}
	}
	else
	{
		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, false, 1).IsValidIndex(1))
		{
			AllPossibleTiles.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, false, 1)[1]);
			
			if (bIsFirstMove)
			{
				if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, false, 2).IsValidIndex(2))
				{
					AllPossibleTiles.Add(Gameboard->GetTilesInADirection(CurrentTile, EDirection::RIGHT, false, 2)[2]);
				}
			}
		}
	}

	if (bIsWhite)
	{
		// Diagonal Left

		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, true, 1).IsValidIndex(1))
		{
			ATile*& Tile = Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTDOWN, true, 1)[1];

			if (Tile->GetHasChessPiece())
			{
				if (!Tile->GetChessPiece()->GetIsWhite())
				{
					AllPossibleTiles.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DIALEFTDOWN, true, 1)[1]);
				}
			}
		}

		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP, true, 1).IsValidIndex(1))
		{
			ATile*& Tile = Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIALEFTUP, true, 1)[1];
			if (Tile)
			{
				if (Tile->GetHasChessPiece())
				{
					if (!Tile->GetChessPiece()->GetIsWhite())
					{
						AllPossibleTiles.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DIALEFTUP, true, 1)[1]);
					}
				}
			}
		}
	}
	else
	{
		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, true, 1).IsValidIndex(1))
		{
			ATile*& Tile = Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTUP, true, 1)[1];
			if (Tile)
			{
				if (Tile->GetHasChessPiece())
				{
					if (Tile->GetChessPiece()->GetIsWhite())
					{
						AllPossibleTiles.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DIARIGHTUP, true, 1)[1]);
					}
				}
			}
		}
		
		if (Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, true, 1).IsValidIndex(1))
		{
			ATile*& Tile = Gameboard->GetTilesInADirection(CurrentTile, EDirection::DIARIGHTDOWN, true, 1)[1];
			if (Tile)
			{
				if (Tile->GetHasChessPiece())
				{
					if (Tile->GetChessPiece()->GetIsWhite())
					{
						AllPossibleTiles.Add(Gameboard->GetTilesInADirection(Tile, EDirection::DIARIGHTDOWN, true, 1)[1]);
					}
				}
			}
		}
	}

	return AllPossibleTiles;
}
