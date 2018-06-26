// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessPiece.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ChessGameModeBase.h"
#include "ChessAI.h"
#include "Board.h"
#include "Board.h"
#include "Tile.h"

// Sets default values
AChessPiece::AChessPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AChessGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		ChessAI = GameMode->GetChessAI();
		if (ChessAI)
		{
		}
	}
	else
	{
	}
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// NOT IN USE
TArray<ATile*>& AChessPiece::GetAllPossibleTiles(ABoard*& GameBoard)
{
	AllPossibleTiles.Empty();
	return AllPossibleTiles;
}

void AChessPiece::MoveToNewTile(ATile*& NewTile, ABoard*& Gameboard)
{
	if (!NewTile || !CurrentTile) {return; }

	// Check to see if we can move here
	if (NewTile->GetIsPossibleMoveLocation())
	{
		// Check to see if we can capture a piece here
		if (NewTile->GetIsPossibleCaptureLocation())
		{
			if (GameMode && NewTile->GetHasChessPiece())
			{
				GameMode->GetGameBoard()->UpdateChessPiecesLeft(NewTile->GetChessPiece(), NewTile->GetChessPiece()->GetIsWhite());
			}
			//if (NewTile->GetRootChessPiece())
			//{
			//	UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: NewTile->RootChessPiece: %s:"), *NewTile->GetRootChessPiece()->GetName())
			//}
			//if (NewTile->GetTempAddedChessPiece())
			//{
			//	UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: NewTile->TempAddedChessPiece: %s:"), *NewTile->GetTempAddedChessPiece()->GetName())
			//}
			//if (NewTile->GetTempCapturedChessPiece())
			//{
			//	UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: NewTile->TempCapturedChessPiece: %s:"), *NewTile->GetTempCapturedChessPiece()->GetName())
			//}
			//if (NewTile->GetTempRemovedChessPiece())
			//{
			//	UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: NewTile->TempRemovedChessPiece: %s:"), *NewTile->GetTempRemovedChessPiece()->GetName())
			//}

			// If the tile has a chesspiece, destroy it
			if (NewTile->GetChessPiece())
			{
				UE_LOG(LogTemp, Warning, TEXT("MoveToNewTile: Is capturing, %s(this = %s) is capturing %s!"), *CurrentTile->GetChessPiece()->GetName(), *GetName(), *NewTile->GetChessPiece()->GetName())
				NewTile->GetChessPiece()->Destroy();
			}
			// If not chesspiece ptr found, check the rootpiece
			else
			{
				// If rootpiece found, destroy that one
				UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: %s is capturing at %s, no chesspiece to destroy! (NULL ERROR)"), *GetName(), *NewTile->GetTileName().ToString())
				if (NewTile->GetRootChessPiece())
				{
					UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: Found NewTile->RootChessPiece: %s. Destroying that one instead"), *NewTile->GetRootChessPiece()->GetName())
					NewTile->GetRootChessPiece()->Destroy();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: %s did not find NewTile->RootChessPiece to destroy instead! (NULL ERROR)"), *GetName())
				}
			}
		}

		UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: Moving %s from %s to %s:"), *GetName(), *CurrentTile->GetTileName().ToString(), *NewTile->GetTileName().ToString())

		// If AI Moved
		if (!bIsWhite)
		{
			CurrentTile->SetAIMovedFromThisTile(true);
		}
		else
		{
			LastTile = nullptr;
		}

		CurrentTile->SetTempLastChessPiece(CurrentTile->GetChessPiece());

		// Set current tile chess piece to null
		CurrentTile->SetChessPice(nullptr);

		// Set the root piece of current tile to null
		CurrentTile->SetRootPieceToNull();

		// Set the current tile to be the new one
		CurrentTile = NewTile;

		// if AI moved
		if (!bIsWhite)
		{
			CurrentTile->SetAIMovedToThisTile(true);
		}

		// Set the root tile of this to current tile
		RootTile = CurrentTile;

		// Set the current piece on current tile to this
		CurrentTile->SetChessPice(this);

		// Set the root piece on current tile to this
		CurrentTile->SetRootPieceFromCurrentChessPiece();

		// Physically move this to the new tile
		SetActorLocation(FVector(CurrentTile->GetActorLocation().X, CurrentTile->GetActorLocation().Y, 20));

		if (bIsFirstMove)
		{
			bIsFirstMove = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MoveToNewTile: Current move is not possible!"))
		UE_LOG(LogTemp, Warning, TEXT("Wanted to move %s from %s to %s"), *GetName(), *CurrentTile->GetTileName().ToString(), *NewTile->GetTileName().ToString())
	}

	Gameboard->RootUndo();
}

void AChessPiece::AI_TestMove(ATile *& NewTile, ABoard*& GameBoard)
{
	if (!NewTile || !CurrentTile) { return; }

	FString Color = "white";
	FString OtherColor = "";
	if (!bIsWhite)
	{
		Color = "black";
		OtherColor = "white";
	}

	// Check if possible to move to the tile
	if (NewTile->GetIsPossibleMoveLocation())
	{
		// If it will be a capture
		if (NewTile->GetIsPossibleCaptureLocation())
		{
			// Get the chesspiece to capture
			if (NewTile->GetChessPiece())
			{
				UE_LOG(LogTemp, Warning, TEXT("AI_TestMove: Capturing %s %s on %s:"), *OtherColor, *NewTile->GetChessPiece()->GetName(), *NewTile->GetTileName().ToString())

				//GameBoard->UpdateChessPiecesLeft(NewTile->GetChessPiece(), NewTile->GetChessPiece()->GetIsWhite());

				// Add the captured piece to the tile TempRemovePointer
				NewTile->SetTempCapturedChessPiece(NewTile->GetChessPiece());

				// "Remove" the piece
				NewTile->SetCurrentChessPieceToNull();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI_TestMove: Moving %s %s from %s to %s:"), *Color, *GetName(), *CurrentTile->GetTileName().ToString(), *NewTile->GetTileName().ToString())
			// Set current chesspiece to the removed one
			CurrentTile->TempRemoveChessPiece(this);
		}

		// "Remove" current piece from current tile
		CurrentTile->SetCurrentChessPieceToNull();

		// Set current tile to last tile
		SetLastTileToCurrentTile();

		// Set the new tile to be the current one
		CurrentTile = NewTile;

		// Set TempAddedChessPiece on new current tile
		CurrentTile->TempAddChessPiece(this);

		// Set the current tile's chesspiece to this one
		CurrentTile->SetChessPice(this);

		CurrentTile->SetTempLastChessPiece(CurrentTile->GetChessPiece());

		if (bIsFirstMove)
		{
			bHasTempFirstMoved = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI_TestMove: Current move is not possible!"))
		if(CurrentTile && NewTile)
		UE_LOG(LogTemp, Warning, TEXT("Wanted to move %s %s from %s to %s"), *Color, *GetName(), *CurrentTile->GetTileName().ToString(), *NewTile->GetTileName().ToString())

	}
}

void AChessPiece::AI_UndoTestMove(FMove*& Move, ABoard *& GameBoard)
{
	if (!Move || !CurrentTile || !GameBoard) { UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: NULL ERROR")) return; }
	
	//** Current tile is the temp moved to **//

	// Set chesspiece to lasttile and reset current tile
	if (LastTile)
	{
		//CurrentTile->SetChessPice(nullptr);
		CurrentTile = LastTile;
		CurrentTile->SetChessPice(this);
		LastTile->SetChessPice(nullptr);
		LastTile = nullptr;

		if (bHasTempFirstMoved)
		{
			bHasTempFirstMoved = false;
			bIsFirstMove = true;
		}
	}

	// If a piece was captured, put it back
	if (Move->PossibleTileToMove->GetTempCapturedChessPiece())
	{
		Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempCapturedChessPiece());
		Move->PossibleTileToMove->GetChessPiece()->SetCurrentTile(Move->PossibleTileToMove);
	}
	else
	{
		//Move->PossibleTileToMove->SetChessPice(nullptr);
		//Move->PossibleTileToMove->SetAllChessPiecePointersToNull();
	}

	// If any new piece was moved here, remove the piece
	if (Move->PossibleTileToMove->GetTempAddedChessPiece())
	{
		Move->PossibleTileToMove->SetCurrentChessPieceToNull();
		Move->PossibleTileToMove->TempAddChessPiece(nullptr);
	}

	// If a piece was captured here, put the captured piece back
	if (Move->PossibleTileToMove->GetTempCapturedChessPiece())
	{
		Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempCapturedChessPiece());
		Move->PossibleTileToMove->SetTempCapturedChessPiece(nullptr);
	}

	// If any piece moved away from here, put it back
	if (Move->PossibleTileToMove->GetTempRemovedChessPiece())
	{
		if (Move->PossibleTileToMove->GetTempRemovedChessPiece() != Move->PossibleTileToMove->GetChessPiece())
		{
			Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempRemovedChessPiece());
		}
		Move->PossibleTileToMove->TempRemoveChessPiece(nullptr);
	}
}

void AChessPiece::SetWhiteMaterial()
{
	if (WhiteMaterial && Mesh->GetMaterial(0) != WhiteMaterial)
	{
		Mesh->SetMaterial(0, WhiteMaterial);

		bIsWhite = true;
	}
}

void AChessPiece::SetWhiteMaterialHighlighted()
{
	if (WhiteMaterialHighlighted && Mesh->GetMaterial(0) != WhiteMaterialHighlighted)
	{
		Mesh->SetMaterial(0, WhiteMaterialHighlighted);
	}
}

void AChessPiece::SetBlackMaterial()
{
	if (BlackMaterial && Mesh->GetMaterial(0) != BlackMaterial)
	{
		Mesh->SetMaterial(0, BlackMaterial);
	}

}

void AChessPiece::SetblackMaterialHighlighted()
{
	if (BlackMaterialHighlighted && Mesh->GetMaterial(0) != BlackMaterialHighlighted)
	{
		Mesh->SetMaterial(0, BlackMaterialHighlighted);
	}
}

void AChessPiece::SetDefaultMaterial()
{
	if (bIsWhite)
	{
		SetWhiteMaterial();
	}
	else
	{
		SetBlackMaterial();
	}
}

FName AChessPiece::GetCurrentTileName()
{
	FName NameToReturn = "";

	if (CurrentTile) 
	{ 
		NameToReturn = CurrentTile->GetTileName();
	}

	return NameToReturn;
}