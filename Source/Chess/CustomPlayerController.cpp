// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ChessGameModeBase.h"
#include "Board.h"
#include "ChessPiece.h"
#include "Tile.h"

ACustomPlayerController::ACustomPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AChessGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameBoard = GameMode->GetGameBoard();
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), 0, CursorHitResult);

	OnHover();
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAction("ToggleSelectObject", IE_Pressed, this, &ACustomPlayerController::OnLeftClick); 
		InputComponent->BindAction("ResetGame", IE_Repeat, this, &ACustomPlayerController::RestartGame);
	}

}

void ACustomPlayerController::RestartGame()
{
	if (!bMenuWindowIsOpen)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld(), true)));
		bMenuWindowIsOpen = true;
	}
}

void ACustomPlayerController::OnHover()
{
	if (CursorHitResult.bBlockingHit)
	{
		// If hovering a chess piece
		if (CursorHitResult.Actor->IsA(AChessPiece::StaticClass()))
		{
			auto Piece = Cast<AChessPiece>(CursorHitResult.Actor);
			if (Piece)
			{
				if (GameMode->GetIfPlayingAgainstPlayer())
				{
					// In case a chess piece or tile was already hovered
					ResetHoveringChessPiece();
					ResetHoveringTile();

					UpdateHoveringChessPiece();
				}
				else
				{
					if (Piece->GetIsWhite() && GameMode->GetIsWhiteTurn())
					{
						// In case a chess piece or tile was already hovered
						ResetHoveringChessPiece();
						ResetHoveringTile();

						UpdateHoveringChessPiece();
					}
				}
			}
		}
		// If hovering a tile
		else if (CursorHitResult.Actor->IsA(ATile::StaticClass()))
		{
			// In case a tile or chess piece was already hovered
			ResetHoveringTile();
			ResetHoveringChessPiece();

			UpdateHoveringTile();
		}
	}
	// If mouse is off the board
	else
	{
		// Resets all hovering
		ResetHoveringChessPiece();
		ResetHoveringTile();
	}

}

void ACustomPlayerController::OnLeftClick()
{
	if (CursorHitResult.Actor->IsA(AChessPiece::StaticClass()))
	{
		// If hovering over piece
		if (CurrentChessPieceHovered)
		{
			// If already clicked a piece
			if (CurrentChessPieceClicked)
			{
				if (!bPieceIsCapturing)
				{
					auto Piece = Cast<AChessPiece>(CursorHitResult.Actor);
					if (Piece)
					{ 
						if (Piece->GetCurrentTile()->GetIsPossibleCaptureLocation())
						{
							CurrentChessPieceClicked->MoveToNewTile(Piece->GetCurrentTile(), true);
							ResetSelectedChessPieceTiles(Piece);
							bPieceIsCapturing = true;
							GameMode->ToggleTurn();
						}
					}
				}
			}

			// Set new piece

			if (GameMode->GetIfPlayingAgainstPlayer())
			{
				if (CurrentChessPieceHovered->GetIsWhite() == GameMode->GetIsWhiteTurn())
				{
					// Resets tiles and deselects piece in case one is already pressed
					ResetSelectedChessPieceTiles();

					CurrentChessPieceClicked = CurrentChessPieceHovered;

					// Set new blue tiles
					UpdateSelectedChessPieceTiles();

					if (bPieceIsCapturing)
					{
						ResetSelectedChessPieceTiles();

						UpdateSelectedChessPieceTiles();
					}
				}
			}
			else
			{
				if (GameMode->GetIsWhiteTurn() && CurrentChessPieceHovered->GetIsWhite())
				{
					// Resets tiles and deselects piece in case one is already pressed
					ResetSelectedChessPieceTiles();

					CurrentChessPieceClicked = CurrentChessPieceHovered;

					// Set new blue tiles
					UpdateSelectedChessPieceTiles();

					if (bPieceIsCapturing)
					{
						ResetSelectedChessPieceTiles();

						UpdateSelectedChessPieceTiles();
					}
				}
			}
		}
	}
	else if (CursorHitResult.Actor->IsA(ATile::StaticClass()))
	{
		if (CurrentHoveredTile)
		{
			// If clicking on hovered tile
			if (CurrentHoveredTile == CursorHitResult.Actor)
			{
				// If a piece is selected
				if (CurrentChessPieceClicked)
				{
					if (CurrentChessPieceClicked->GetIsWhite() == GameMode->GetIsWhiteTurn())
					{
						if (CurrentHoveredTile->GetIsPossibleCaptureLocation())
						{
							CurrentChessPieceClicked->MoveToNewTile(CurrentHoveredTile, true);
							GameMode->ToggleTurn();
						}
						else if (CurrentHoveredTile->GetIsPossibleMoveLocation())
						{
							CurrentChessPieceClicked->MoveToNewTile(CurrentHoveredTile);
							GameMode->ToggleTurn();
						}
						ResetSelectedChessPieceTiles();

						UpdateSelectedChessPieceTiles();
					}
				}
			}
		}
	}
}
// "Dehovers" chess piece and resets pointer
void ACustomPlayerController::ResetHoveringChessPiece()
{
	if (CurrentChessPieceHovered)
	{
		if (CurrentChessPieceHovered != CurrentChessPieceClicked)
		{
			CurrentChessPieceHovered->SetDefaultMaterial();
		}
		CurrentChessPieceHovered = nullptr;
	}
}

// When hovering a chess piece
void ACustomPlayerController::UpdateHoveringChessPiece()
{
	auto ChessPiece = Cast<AChessPiece>(CursorHitResult.Actor);
	if (ChessPiece)
	{
		CurrentChessPieceHovered = ChessPiece;
		if (CurrentChessPieceHovered->GetIsWhite())
		{
			CurrentChessPieceHovered->SetWhiteMaterialHighlighted();
		}
		else
		{
			CurrentChessPieceHovered->SetblackMaterialHighlighted();
		}
	}
}

// "Dehovers" a tile and resets pointer
void ACustomPlayerController::ResetHoveringTile()
{
	if (CurrentHoveredTile)
	{
		if (CurrentHoveredTile->GetIsPossibleCaptureLocation())
		{
			CurrentHoveredTile->SetPossibleCaptureMaterial();
		}
		else if (CurrentHoveredTile->GetIsPossibleMoveLocation())
		{
			CurrentHoveredTile->SetPossibleMoveMaterial();
		}
		else
		{
			CurrentHoveredTile->SetDefaultMaterial();
		}
		CurrentHoveredTile = nullptr;
	}
}

// When hovering a tile
void ACustomPlayerController::UpdateHoveringTile()
{
	CurrentHoveredTile = Cast<ATile>(CursorHitResult.Actor);
	if (CurrentHoveredTile->GetIsPossibleMoveLocation())
	{
		CurrentHoveredTile->SetHighlightedPossibleMoveMaterial();
	}

	if (CurrentHoveredTile->GetIsPossibleCaptureLocation())
	{
		CurrentHoveredTile->SetHighlightedPossibleCaptureMaterial();
	}
}

// Resets blue tiles and deselects piece
void ACustomPlayerController::ResetSelectedChessPieceTiles(AChessPiece* ChessPiece)
{
	if (ChessPiece)
	{
		for (auto& Tile : CurrentChessPieceClicked->GetAllPossibleTiles())
		{
			Tile->SetDefaultMaterial();
			Tile->SetIsPossibleMoveLocation(false);
			if (Tile->GetIsPossibleCaptureLocation())
			{
				Tile->SetIsPossibleCaptureLocation(false);
			}
		}
	}

	if (CurrentPossibleMoveLocationTiles.Num())
	{
		for (auto& Tile : CurrentPossibleMoveLocationTiles)
		{
			Tile->SetDefaultMaterial();
			if (Tile->GetIsPossibleCaptureLocation())
			{
				Tile->SetIsPossibleCaptureLocation(false);
			}
			Tile->SetIsPossibleMoveLocation(false);
		}
		CurrentPossibleMoveLocationTiles.Empty();
	}
	if (CurrentChessPieceClicked)
	{
		CurrentChessPieceClicked->SetDefaultMaterial();
		CurrentChessPieceClicked = nullptr;
		bPieceIsCapturing = false;
	}
}

// Updates the possible move locations when a chess piece is selected
void ACustomPlayerController::UpdateSelectedChessPieceTiles()
{
	if (CurrentChessPieceClicked)
	{
		CurrentPossibleMoveLocationTiles.Empty();

		for (auto& Tile : CurrentChessPieceClicked->GetAllPossibleTiles())
		{
			if (Tile->GetIsPossibleCaptureLocation())
			{
				Tile->SetPossibleCaptureMaterial();
			}
			else
			{
				Tile->SetPossibleMoveMaterial();
			}

			Tile->SetIsPossibleMoveLocation(true);
			CurrentPossibleMoveLocationTiles.Add(Tile);
		}
	}
}
