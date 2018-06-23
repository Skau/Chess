// Fill out your copyright notice in the Description page of Project Settings.

#include "KingPiece.h"
#include "Tile.h"

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

TArray<ATile*>& AKingPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetTileUp())
	{
		if (CurrentTile->GetTileUp()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileUp()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileUp());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileUp());
		}
	}
	if (CurrentTile->GetTileDown())
	{
		if (CurrentTile->GetTileDown()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileDown()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileDown()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileDown());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDown());
		}
	}
	if (CurrentTile->GetTileLeft())
	{
		if (CurrentTile->GetTileLeft()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileLeft()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileLeft()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileLeft());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileLeft());
		}
	}
	if (CurrentTile->GetTileRight())
	{
		if (CurrentTile->GetTileRight()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileRight()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileRight()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileRight());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileRight());
		}
	}
	if (CurrentTile->GetTileDiagonalRightUp())
	{
		if (CurrentTile->GetTileDiagonalRightUp()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp());
		}
	}
	if (CurrentTile->GetTileDiagonalRightDown())
	{
		if (CurrentTile->GetTileDiagonalRightDown()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown());
		}
	}
	if (CurrentTile->GetTileDiagonalLeftUp())
	{
		if (CurrentTile->GetTileDiagonalLeftUp()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp());
		}
	}
	if (CurrentTile->GetTileDiagonalLeftDown())
	{
		if (CurrentTile->GetTileDiagonalLeftDown()->GetHasChessPiece())
		{
			if (CurrentTile->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
			{
				CurrentTile->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown());
			}
		}
		else
		{
			PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown());
		}
	}

	return PossibleTilesToMove;
}
