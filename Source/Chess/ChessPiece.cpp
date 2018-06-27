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

			// If the tile has a chesspiece, destroy it
			if (NewTile->GetChessPiece())
			{
				//UE_LOG(LogTemp, Warning, TEXT("MoveToNewTile: Is capturing, %s(this = %s) is capturing %s!"), *CurrentTile->GetChessPiece()->GetName(), *GetName(), *NewTile->GetChessPiece()->GetName())
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
			LastTiles.Empty();

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

		// Set current tile root piece / current piece if they are different 
		FixTilesAtEndOfRound();
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
	FString OtherColor = "black";
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
		LastTiles.Add(CurrentTile);
		SetLastTileToCurrentTile();

		// Set the new tile to be the current one
		CurrentTile = NewTile;

		// Set TempAddedChessPiece on new current tile
		CurrentTile->TempAddChessPiece(this);

		// Set the current tile's chesspiece to this one
		CurrentTile->SetChessPice(this);

		//CurrentTile->SetTempLastChessPiece(CurrentTile->GetChessPiece());

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

void AChessPiece::AI_UndoTestMove(FMove*& Move, ABoard *& GameBoard, bool IsLastRegularUndo)
{
	if (!Move || !CurrentTile || !GameBoard) { UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Move / CurrentTile / Gameboard NULL ERROR")) return; }
	
	if (!Move->ChessPiece || !Move->PossibleTileToMove) { UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Move Piece / Tile NULL ERROR")) return; }
	FString Color = "white";
	FString OtherColor = "black";
	if (!Move->ChessPiece->GetIsWhite())
	{
		Color = "black";
		OtherColor = "white";
	}
	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: %s %s on %s "),
		*Color, *Move->ChessPiece->GetName(), *Move->ChessPiece->GetCurrentTile()->GetTileName().ToString())


	//** Current tile is the temp moved to **//

	// Set chesspiece to lasttile and reset current tile

	if (LastTiles.Num())
	{
		if (IsLastRegularUndo)
		{
			UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: Is last regular undo!"))
			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove [%s %s]: CurrentTile(%s) set to LastTile(%s) "),
			*Color, *this->GetName(), *this->GetCurrentTile()->GetTileName().ToString(), *LastTiles[0]->GetTileName().ToString())

			ATile*& LastTile = LastTiles[0];

			CurrentTile = LastTile;

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: CurrentTile(%s) set chesspiece to %s (this)"), *this->CurrentTile->GetTileName().ToString(), *this->GetName())

			CurrentTile->SetChessPice(this);

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set chesspiece to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())

			LastTile->SetChessPice(nullptr);

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())
			LastTile = nullptr;

			LastTiles.Empty();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: Is NOT last regular undo!"))
			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove [%s %s]: CurrentTile(%s) set to LastTile(%s) "),
			*Color, *this->GetName(), *this->GetCurrentTile()->GetTileName().ToString(), *this->GetLastTile()->GetTileName().ToString())

			ATile*& LastTile = LastTiles.Last();

			CurrentTile = LastTiles.Last();

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: CurrentTile(%s) set chesspiece to %s (this)"), *this->CurrentTile->GetTileName().ToString(), *this->GetName())

			CurrentTile->SetChessPice(this);

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set chesspiece to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())

			LastTile->SetChessPice(nullptr);

			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())
			LastTile = nullptr;

			LastTiles.Pop(true);
		}
	
		if (bHasTempFirstMoved)
		{
			bHasTempFirstMoved = false;
			bIsFirstMove = true;
		}
	}

	//if (LastTile)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove [%s %s]: CurrentTile(%s) set to LastTile(%s) "),
	//		*Color, *this->GetName(), *this->GetCurrentTile()->GetTileName().ToString(), *this->GetLastTile()->GetTileName().ToString())
	//	//CurrentTile->SetChessPice(nullptr);
	//	CurrentTile = LastTile;
	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: CurrentTile(%s) set chesspiece to %s (this)"), *this->CurrentTile->GetTileName().ToString(), *this->GetName())
	//	CurrentTile->SetChessPice(this);

	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set chesspiece to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())

	//	LastTile->SetChessPice(nullptr);

	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: LastTile set to null"), *Move->ChessPiece->GetLastTile()->GetTileName().ToString())
	//	LastTile = nullptr;

	//	if (bHasTempFirstMoved)
	//	{
	//		bHasTempFirstMoved = false;
	//		bIsFirstMove = true;
	//	}
	//}

	// Rewrote if piece was captured (now sets chess piece tiles first, then sets tile piece pointers.
	// Swapped places of the two if checks below


	UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: (Move->PossibleTile) If piece was captured:"))
	// If a piece was captured, put it back
	if (Move->PossibleTileToMove->GetTempCapturedChessPiece())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Move->PossibleTile (%s) has TempCapturedPiece (%s)"), *Move->PossibleTileToMove->GetTileName().ToString(), *Move->PossibleTileToMove->GetTempCapturedChessPiece()->GetName())
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Move->PossibleTile (%s) SetChessPiece to TempCapturedPiece (%s)"), *Move->PossibleTileToMove->GetTileName().ToString(), *Move->PossibleTileToMove->GetTempCapturedChessPiece()->GetName())
		Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempCapturedChessPiece());
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Move->PossibleTile->GetChessPiece (%s) SetCurrentTile to %s ( Tile is Move->PossibleTileToMove)"), *Move->PossibleTileToMove->GetChessPiece()->GetName(), *Move->PossibleTileToMove->GetTileName().ToString())
		Move->PossibleTileToMove->GetChessPiece()->SetCurrentTile(Move->PossibleTileToMove);
		//Move->PossibleTileToMove->SetRootPieceFromCurrentChessPiece();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: No piece was captured here! (%s)"), *Move->PossibleTileToMove->GetTileName().ToString())
		//Move->PossibleTileToMove->SetChessPice(nullptr); 
		//Move->PossibleTileToMove->SetAllChessPiecePointersToNull();
	}
 
	UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: (Move->PossibleTile) If any new piece was moved here:"))
	// If any new piece was moved here
	if (Move->PossibleTileToMove->GetTempAddedChessPiece())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: If the current chess piece equals the temp one:"))
		// If the current chess piece equals the temp one, remove
		if (Move->PossibleTileToMove->GetChessPiece() == Move->PossibleTileToMove->GetTempAddedChessPiece())
		{
			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: It does equal, so setting CurrentChessPiece(%s) and TempAdded(%s) to nullptr"), *Move->PossibleTileToMove->GetChessPiece()->GetName(), *Move->PossibleTileToMove->GetTempAddedChessPiece()->GetName())
			Move->PossibleTileToMove->SetCurrentChessPieceToNull();
			Move->PossibleTileToMove->TempAddChessPiece(nullptr);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: No piece was moved here! (%s)"), *Move->PossibleTileToMove->GetTileName().ToString())
	}

	//UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: If a piece was captured here, put the captured piece back:"))
	//// If a piece was captured here, put the captured piece back
	//if (Move->PossibleTileToMove->GetTempCapturedChessPiece())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Does have TempCapturedPiece(%s), Move->PossibleTile set ChessPiece to TempCaptured (current is %s) "), *Move->PossibleTileToMove->GetTempCapturedChessPiece()->GetName(), *Move->PossibleTileToMove->GetChessPiece())
	//	Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempCapturedChessPiece());
	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: TempCaptured set to nullptr"))
	//	Move->PossibleTileToMove->SetTempCapturedChessPiece(nullptr);
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: No piece was captured here!"))
	//}

	UE_LOG(LogTemp, Error, TEXT("AI_UndoTestMove: If any piece moved away from here, put it back:"))
	// If any piece moved away from here, put it back
	if (Move->PossibleTileToMove->GetTempRemovedChessPiece())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: Does have TempRemovedChessPiece(%s). If it doesn't equal CurrentChessPiece, set current to tempremoved."), *Move->PossibleTileToMove->GetTempRemovedChessPiece()->GetName())
		if (Move->PossibleTileToMove->GetTempRemovedChessPiece() != Move->PossibleTileToMove->GetChessPiece())
		{
			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: It does not equal, setting new current to tempremoved."))
			Move->PossibleTileToMove->SetChessPice(Move->PossibleTileToMove->GetTempRemovedChessPiece());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: It does equal doing nothing"))
		}
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: TempRemoved set to nullptr"))
		Move->PossibleTileToMove->TempRemoveChessPiece(nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI_UndoTestMove: No piece moved away from this tile! (%s)"), *Move->PossibleTileToMove->GetTileName().ToString())
	}

	// Moved Last Tile stuff to after if checks

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

void AChessPiece::FixTilesAtEndOfRound()
{
	if (CurrentTile->GetChessPiece() != this)
	{
		CurrentTile->SetChessPice(this);
		CurrentTile->SetRootPieceFromCurrentChessPiece();
	}
}