// Fill out your copyright notice in the Description page of Project Settings.

#include "KnightPiece.h"
#include "Tile.h"

void AKnightPiece::BeginPlay()
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

TArray<ATile*>& AKnightPiece::GetAllPossibleTiles(ABoard*& GameBoard, bool IsAI)
{
	PossibleTilesToMove.Empty();

	// AI
	if (IsAI)
	{
		if (CurrentTile->GetLastSavedInfo()->ChessPiece == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetLastSavedInfo()->ChessPieceNULL ERROR")) return PossibleTilesToMove; }

		if (CurrentTile->GetTileDiagonalRightUp())
		{
			if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
				}
			}

			if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
				}
			}
		}
		if (CurrentTile->GetTileDiagonalRightDown())
		{
			if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
				}

			}

			if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
				}
			}
		}

		if (CurrentTile->GetTileDiagonalLeftUp())
		{
			if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
				}
			}

			if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft());
				}
			}
		}

		if (CurrentTile->GetTileDiagonalLeftDown())
		{
			if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
				}
			}

			if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetLastSavedInfo()->ChessPiece)
				{
					if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetLastSavedInfo()->ChessPiece->GetIsWhite() != CurrentTile->GetLastSavedInfo()->ChessPiece->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
				}
			}
		}
	}
	// Player
	else
	{
		if (CurrentTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("Piece: GetAllPossibleTiles: CurrentTile->GetHasChessPiece() NULL ERROR")) return PossibleTilesToMove; }

		if (CurrentTile->GetTileDiagonalRightUp())
		{
			if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileUp());
				}
			}

			if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight())
			{
				if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightUp()->GetTileRight());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightUp()->GetTileRight()->SetIsPossibleMoveLocation(true);
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
						CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileDown());
				}

			}

			if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight())
			{
				if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalRightDown()->GetTileRight());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalRightDown()->GetTileRight()->SetIsPossibleMoveLocation(true);
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
						CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileUp()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileUp());
				}
			}

			if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft())
			{
				if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftUp()->GetTileLeft()->SetIsPossibleMoveLocation(true);
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
						CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileDown()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileDown());
				}
			}

			if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft())
			{
				if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetHasChessPiece())
				{
					if (CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->GetChessPiece()->GetIsWhite() != CurrentTile->GetChessPiece()->GetIsWhite())
					{
						CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleMoveLocation(true);
						CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
						PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
					}
				}
				else
				{
					CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft()->SetIsPossibleMoveLocation(true);
					PossibleTilesToMove.Add(CurrentTile->GetTileDiagonalLeftDown()->GetTileLeft());
				}
			}
		}
	}
	return PossibleTilesToMove;
}
