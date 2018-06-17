// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightPiece.h"
#include "Tile.h"

TArray<ATile*>& AKnightPiece::GetAllPossibleTiles()
{
	PossibleTilesToMove.Empty();

	if (CurrentTile->GetTileDiagonalRightUp())
	{
		if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp())
		{
			if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
			}
		}

		if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight())
		{
			if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
			}
		}
	}
	if (CurrentTile->GetTileDiagonalRightDown())
	{
		if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown())
		{
			if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
			}

		}

		if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight())
		{
			if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
			}
		}
	}

	if (CurrentTile->GetTileDiagonalLeftUp())
	{
		if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp())
		{
			if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
			}
		}

		if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft())
		{
			if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft());
			}
		}
	}

	if (CurrentTile->GetTileDiagonalLeftDown())
	{
		if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown())
		{
			if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
			}
		}

		if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft())
		{
			if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetHasChessPiece())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
				}
			}
			else
			{
				PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
			}
		}
	}

	return PossibleTilesToMove;
}
