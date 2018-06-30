// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Engine/World.h"
#include "Kismet/Gameplaystatics.h"
#include "Components/StaticMeshComponent.h"
#include "ChessGameModeBase.h"
#include "Tile.h"
#include "ChessAI.h"
#include "ChessPiece.h"
#include "PawnPiece.h"
#include "KnightPiece.h"
#include "BishopPiece.h"
#include "QueenPiece.h"
#include "RookPiece.h"
#include "KingPiece.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Tiles.Reserve(64);
	AllWhitePieces.Reserve(16);
	AllBlackPieces.Reserve(16);

	AllBlackPieces.Reserve(16);
	AllWhitePieces.Reserve(16);
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnTiles(false);

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
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::SpawnTiles(bool bIsTemp)
{
	FString Letter = "h";
	int Number = 1;

	bool bUseLightMaterial = true;

	FVector SpawnLocation = FVector(43.75, 43.75, 100);

	if (TileActor)
	{
		for (int i = 0; i < 64; ++i)
		{
			auto Tile = GetWorld()->SpawnActor<ATile>(TileActor, FVector(0), GetActorRotation());

			Tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			if (i == 0)
			{
				Tile->SetDarkMaterial();
			}
			else if (i % 8 == 0)
			{
				if (bUseLightMaterial)
				{
					Tile->SetDarkMaterial();
					if (!bIsTemp)
					{
						SpawnLocation.X = 43.75;
						SpawnLocation.Y -= 12.5;
					}
					else
					{
						SpawnLocation.X = 20000;
						SpawnLocation.Y -= 168.75;
					}
				}
				else if (!bUseLightMaterial)
				{
					Tile->SetLightMaterial();
					if (!bIsTemp)
					{
						SpawnLocation.X = 43.75;
						SpawnLocation.Y -= 12.5;
					}
					else
					{
						SpawnLocation.X = 20000;
						SpawnLocation.Y -= 168.75;
					}
				}
			}
			else
			{
				if (bUseLightMaterial)
				{
					Tile->SetLightMaterial();
					bUseLightMaterial = false;
				}
				else
				{
					Tile->SetDarkMaterial();
					bUseLightMaterial = true;
				}
				SpawnLocation.X -= 12.5;
			}

			Tile->SetActorRelativeLocation(SpawnLocation);
			Tile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Tile->index = i;
			FString Name = Letter + FString::FromInt(Number);
			Tile->SetName(FName(*Name));
			if (Letter == "h")
			{
				Letter = "g";
			}
			else if (Letter == "g")
			{
				Letter = "f";
			}
			else if (Letter == "f")
			{
				Letter = "e";
			}
			else if (Letter == "e")
			{
				Letter = "d";
			}
			else if (Letter == "d")
			{
				Letter = "c";
			}
			else if (Letter == "c")
			{
				Letter = "b";
			}
			else if (Letter == "b")
			{
				Letter = "a";
			}
			else if (Letter == "a")
			{
				Letter = "h";
				Number++;
			}
			Tiles.Add(Tile);
		}

		UpdateTilePointers();
	}
}

void ABoard::UpdateTilePointers()
{
	if (Tiles.Num())
	{
		for (int i = 0; i < 64; ++i)
		{
			if (Tiles[i])
			{
				if ((i == 7 || i == 15 || i == 23 || i == 31 || i == 39 || i == 47 || i == 55 || i == 63))
				{
					Tiles[i]->SetTileDown(nullptr);
					Tiles[i]->SetTileDiagonalLeftDown(nullptr);
					Tiles[i]->SetTileDiagonalRightDown(nullptr);
				}
				else
				{
					if (i + 1 >= 0 && i + 1 <= 63)
					{
						if (Tiles[i + 1])
						{
							Tiles[i]->SetTileDown(Tiles[i + 1]);
						}
					}

					if (i + 9 >= 0 && i + 9 <= 63)
					{
						if (Tiles[i + 9])
						{
							Tiles[i]->SetTileDiagonalLeftDown(Tiles[i + 9]);
						}
					}

					if (i - 7 >= 0 && i - 7 <= 63)
					{
						if (Tiles[i - 7])
						{
							Tiles[i]->SetTileDiagonalRightDown(Tiles[i - 7]);
						}
					}
				}
				if ((i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48 || i == 56 || i == 64))
				{
					Tiles[i]->SetTileUp(nullptr);
					Tiles[i]->SetTileDiagonalRightUp(nullptr);
					Tiles[i]->SetTileDiagonalLeftUp(nullptr);
				}
				else
				{
					if (i - 1 >= 0 && i - 1 <= 63)
					{
						if (Tiles[i - 1])
						{
							if (i % 8 == 0)
							{
								Tiles[i]->SetTileUp(nullptr);
							}
							else
							{
								Tiles[i]->SetTileUp(Tiles[i - 1]);
							}
						}
					}

					if (i + 7 >= 0 && i + 7 <= 63)
					{
						if (Tiles[i + 7])
						{
							Tiles[i]->SetTileDiagonalLeftUp(Tiles[i + 7]);
						}
					}
					if (i - 9 >= 0 && i - 9 <= 63)
					{
						if (Tiles[i - 9])
						{
							Tiles[i]->SetTileDiagonalRightUp(Tiles[i - 9]);
						}
					}
				}

				if (i + 8 >= 0 && i + 8 <= 63)
				{
					if (Tiles[i + 8])
					{
						Tiles[i]->SetTileLeft(Tiles[i + 8]);
					}
				}
				if (i - 8 >= 0 && i - 8 <= 63)
				{
					if (Tiles[i - 8])
					{
						Tiles[i]->SetTileRight(Tiles[i - 8]);
					}
				}
			}
		}
	}
}

void ABoard::SpawnChessPieces()
{
	FVector SpawnLocation = FVector(0);

	for (int i = 0; i < 64; ++i)
	{
		if (i < 16)
		{
			FRotator WhiteSpawnRotation = FRotator(0, 180, 0);
			if (i == 0 || i == 7)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<ARookPiece>(
					RookPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::Rook);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}

			if (i == 1 || i == 6)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AKnightPiece>(
					KnightPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::Knight);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}

			if (i == 2 || i == 5)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<ABishopPiece>(
					BishopPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::Bishop);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}

			if (i == 3)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AQueenPiece>(
					QueenPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::Queen);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}

			if (i == 4)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AKingPiece>(
					KingPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::King);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}

			if (PawnPiece && i <= 15 && i >= 8)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<APawnPiece>(
					PawnPiece, SpawnLocation, WhiteSpawnRotation);
				piece->SetWhiteMaterial();
				piece->SetPieceType(EPieceType::Pawn);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllWhitePieces.Add(piece);
			}
		}
		else if (i > 47)
		{
			if (i == 63 || i == 56)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<ARookPiece>(
					RookPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::Rook);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}

			if (i == 62 || i == 57)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AKnightPiece>(
					KnightPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::Knight);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}

			if (i == 61 || i == 58)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<ABishopPiece>(
					BishopPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::Bishop);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}

			if (i == 60)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AKingPiece>(
					KingPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::King);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}

			if (i == 59)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<AQueenPiece>(
					QueenPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::Queen);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}

			if (PawnPiece && i <= 55 && i >= 48)
			{
				SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
				auto piece = GetWorld()->SpawnActor<APawnPiece>(
					PawnPiece, SpawnLocation, FRotator(0));
				piece->SetBlackMaterial();
				piece->SetPieceType(EPieceType::Pawn);
				piece->SetCurrentTile(Tiles[i]);
				piece->SetRootTileToCurrentTile();
				Tiles[i]->SetChessPice(piece);
				Tiles[i]->SetRootPieceFromCurrentChessPiece();
				AllBlackPieces.Add(piece);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("AllFriendlyPieces: %i"), AllWhitePieces.Num())
	UE_LOG(LogTemp, Warning, TEXT("AllEnemyPieces: %i"), AllBlackPieces.Num())
}

void ABoard::UpdateChessPiecesLeft(AChessPiece* ChessPieceToRemove, bool IfWhite)
{
	if (ChessPieceToRemove->GetPieceType() == EPieceType::King)
	{
		if (GameMode)
		{
			GameMode->SetGameIsOver(!IfWhite);
			return;
		}
	}

	if (IfWhite)
	{
		AllWhitePieces.Remove(ChessPieceToRemove);
	}
	else
	{
		AllBlackPieces.Remove(ChessPieceToRemove);
	}
}

ABoard* ABoard::CreateTempGameBoard()
{
	auto BoardToReturn = GetWorld()->SpawnActor<ABoard>(GameMode->GetBoardBP(), FVector(50000,50000,50000), FRotator(0));

	//BoardToReturn->SpawnTiles(true);

	for (auto& Piece : AllWhitePieces)
	{
		SpawnChessPiecesTemp(BoardToReturn, Piece, Piece->GetCurrentTile());
	}

	for (auto& Piece : AllBlackPieces)
	{
		SpawnChessPiecesTemp(BoardToReturn, Piece, Piece->GetCurrentTile());
	}

	return BoardToReturn;
}

void ABoard::SpawnChessPiecesTemp(ABoard*& GameBoard, AChessPiece* ChessPieceToCopy, ATile* TileToSpawnOn)
{
	for (auto& Tile : GameBoard->Tiles)
	{
		if (TileToSpawnOn->GetTileName().IsEqual(Tile->GetTileName()))
		{
			FVector SpawnLocation = FVector(Tile->GetActorLocation().X, Tile->GetActorLocation().Y, 20);
			auto Type = ChessPieceToCopy->GetPieceType();
			AChessPiece* NewChessPiece = nullptr;
			switch (Type)
			{
			case EPieceType::Pawn:
				NewChessPiece = GetWorld()->SpawnActor<APawnPiece>(
					PawnPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::Pawn);
				break;
			case EPieceType::Rook:
				NewChessPiece = GetWorld()->SpawnActor<ARookPiece>(
					RookPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::Rook);
				break;
			case EPieceType::Knight:
				NewChessPiece = GetWorld()->SpawnActor<AKnightPiece>(
					KnightPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::Knight);
				break;
			case EPieceType::Bishop:
				NewChessPiece = GetWorld()->SpawnActor<ABishopPiece>(
					BishopPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::Bishop);
				break;
			case EPieceType::King:
				NewChessPiece = GetWorld()->SpawnActor<AKingPiece>(
					KingPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::King);
				break;
			case EPieceType::Queen:
				NewChessPiece = GetWorld()->SpawnActor<AQueenPiece>(
					QueenPiece, SpawnLocation, FRotator(0));
				NewChessPiece->SetPieceType(EPieceType::Queen);
				break;
			default:
				break;
			}
			NewChessPiece->SetCurrentTile(Tile);
			Tile->SetChessPice(NewChessPiece);

			if (ChessPieceToCopy->GetIsWhite())
			{
				ChessPieceToCopy->SetWhiteMaterial();
				GameBoard->AllWhitePieces.Add(NewChessPiece);
			}
			else
			{
				ChessPieceToCopy->SetBlackMaterial();
				GameBoard->AllBlackPieces.Add(NewChessPiece);
			}
		}
	}
}

ATile* ABoard::GetTileByName(FName Tilename)
{
	ATile* TileToReturn = nullptr;

	for (auto& Tile : Tiles)
	{
		if (Tile->GetTileName() == Tilename)
		{
			TileToReturn = Tile;
			return TileToReturn;
		}
	}

	return TileToReturn;
}

void ABoard::DestroyBoard()
{
	for (auto& Piece : AllWhitePieces)
	{
		if (Piece)
		{
			//AllWhitePieces.Remove(Piece);
			Piece->Destroy();
			//Piece = nullptr;
		}
	}

	for (auto& Piece : AllBlackPieces)
	{
		if (Piece)
		{
			//AllWhitePieces.Remove(Piece);
			Piece->Destroy();
			//Piece = nullptr;
		}
	}

	for (auto& Tile : Tiles)
	{
		if (Tile)
		{
			//Tiles.Remove(Tile);
			Tile->Destroy();
			//Tile = nullptr;
		}
	}
	Destroy();
}

void ABoard::SaveCurrentChessPieces(bool IsRoot)
{
	for (auto& Tile : Tiles)
	{
		if (Tile->GetHasChessPiece())
		{
			if (IsRoot)
			{
				Tile->SetRootPieceFromCurrentChessPiece();
			}
		}
	}
}

void ABoard::ResetAllChessPiecesToLastState()
{
	for (auto& Tile : Tiles)
	{
		Tile->ResetTileToLastState();
	}
}

void ABoard::RootUndo()
{
	UE_LOG(LogTemp, Warning, TEXT("Root undo"))

	// For all tiles on the board
	for (auto& Tile : Tiles)
	{
		//Tile->SetCurrentChessPieceToNull();

		// Reset Tile color and capture/move flags
		Tile->SetDefaultMaterial();

		// Set the root piece to be the current one
		Tile->ResetToRootChessPiece();

		// If there is a piece on the tile
		if (Tile->GetHasChessPiece())
		{
			// if the current root tile is not the current tile
			if (Tile->GetChessPiece()->GetCurrentTile())
			{
				if (Tile->GetChessPiece()->GetCurrentRootTile())
				{
					if (Tile->GetChessPiece()->GetCurrentTile() != Tile->GetChessPiece()->GetCurrentRootTile())
					{
						Tile->GetChessPiece()->SetCurrentTile(Tile->GetChessPiece()->GetCurrentRootTile());
					}
				}
			}
			
			// If AI Moved away from this tile, reset all pointers.
			if (Tile->GetAIMovedFromThisTile())
			{
				Tile->SetAllChessPiecePointersToNull();
				Tile->SetAIMovedFromThisTile(false);
			}

			// If AI Moved to this tile, root piece equals current piece
			if (Tile->GetAIMovedToThisTile())
			{
				Tile->SetRootPieceFromCurrentChessPiece();
				Tile->SetAIMovedToThisTile(false);
			}
			//Tile->GetChessPiece()->SetCurrentTileToRootTile();
		}
		// If no piece on tile, set all pointers to null
		else
		{
			//???
			//Tile->SetAllChessPiecePointersToNull();
		}

		
		if (Tile->GetChessPiece())
		{
			if (Tile->GetChessPiece()->GetAllLastTiles().Num())
			{
				//ATile*& LastTile = Tile->GetChessPiece()->GetAllLastTiles()[0];

				//Tile->GetChessPiece()->SetCurrentTile(LastTile);

				//Tile->GetChessPiece()->GetCurrentTile()->SetChessPice(Tile->GetChessPiece());

				//LastTile->SetChessPice(nullptr);

				//LastTile = nullptr;

				Tile->GetChessPiece()->EmptyAllLastTiles();
			}
		}
	}
}

TArray<ATilePtr>& ABoard::GetTilesInADirection(ATilePtr& StartTile, EDirection Direction, bool CanCapture, int NumberOfTiles)
{
	for (auto& Tile : Tiles)
	{
		Tile->SetIsPossibleCaptureLocation(false);
		Tile->SetIsPossibleMoveLocation(false);
	}

	if (AllTilesInADirection.Num())
	{
		AllTilesInADirection.Empty();
	}

	if (StartTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return AllTilesInADirection; }

	if (StartTile)
	{
		StartTile->SetIsPossibleCaptureLocation(false);
		StartTile->SetIsPossibleMoveLocation(false);
		AllTilesInADirection.Add(StartTile);
		switch (Direction)
		{
		case EDirection::UP:
		for (int i = 1; i <= NumberOfTiles; ++i)
		{
			if (AllTilesInADirection.Last()->GetTileUp())
			{
				if (AllTilesInADirection.Last()->GetTileUp()->GetHasChessPiece())
				{
					if (AllTilesInADirection.Last()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
					{
						AllTilesInADirection.Last()->GetTileUp()->SetIsPossibleCaptureLocation(true);
						AllTilesInADirection.Last()->GetTileUp()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileUp());
						break;
					}
					else
					{
						break;
					}
				}
				else
				{
					AllTilesInADirection.Last()->GetTileUp()->SetIsPossibleMoveLocation(true);
					AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileUp());
				}
			}
			else
			{
				break;
			}
		}
		break;
		case EDirection::DOWN:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileDown())
				{
					if (AllTilesInADirection.Last()->GetTileDown()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileDown()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileDown()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDown());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileDown()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDown());
					}
				}
				else
				{
					break;
				}
			}
			break;
		case EDirection::LEFT:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileLeft())
				{
					if (AllTilesInADirection.Last()->GetTileLeft()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileLeft()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileLeft());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileLeft()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileLeft());
					}
				}
				else
				{
					break;
				}
			}
			break;
		case EDirection::RIGHT:
			if (AllTilesInADirection.Last()->GetTileRight())
			{
				if (AllTilesInADirection.Last()->GetTileRight()->GetHasChessPiece())
				{
					if (AllTilesInADirection.Last()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
					{
						AllTilesInADirection.Last()->GetTileRight()->SetIsPossibleCaptureLocation(true);
						AllTilesInADirection.Last()->GetTileRight()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileRight());
						break;
					}
					else
					{
						break;
					}
				}
				else
				{
					AllTilesInADirection.Last()->GetTileRight()->SetIsPossibleMoveLocation(true);
					AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileRight());
				}
			}
			else
			{
				break;
			}
			break;
		case EDirection::DIARIGHTUP:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileDiagonalRightUp())
				{
					if (AllTilesInADirection.Last()->GetTileDiagonalRightUp()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileDiagonalRightUp()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalRightUp());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileDiagonalRightUp()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalRightUp());
					}
				}
				else
				{
					break;
				}
			}
			break;
		case EDirection::DIARIGHTDOWN:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileDiagonalRightDown())
				{
					if (AllTilesInADirection.Last()->GetTileDiagonalRightDown()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileDiagonalRightDown()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalRightDown());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileDiagonalRightDown()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalRightDown());
					}
				}
				else
				{
					break;
				}
			}
			break;
		case EDirection::DIALEFTUP:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileDiagonalLeftUp())
				{
					if (AllTilesInADirection.Last()->GetTileDiagonalLeftUp()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileDiagonalLeftUp()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalLeftUp());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileDiagonalLeftUp()->SetIsPossibleMoveLocation(true);
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalLeftUp());
					}
				}
				else
				{
					break;
				}
			}
			break;
		case EDirection::DIALEFTDOWN:
			for (int i = 1; i <= NumberOfTiles; ++i)
			{
				if (AllTilesInADirection.Last()->GetTileDiagonalLeftDown())
				{
					if (AllTilesInADirection.Last()->GetTileDiagonalLeftDown()->GetHasChessPiece())
					{
						if (AllTilesInADirection.Last()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartTile->GetChessPiece()->GetIsWhite() && CanCapture)
						{
							AllTilesInADirection.Last()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
							AllTilesInADirection.Last()->GetTileDiagonalLeftDown()->SetIsPossibleMoveLocation(true);
							AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalLeftDown());
							break;
						}
						else
						{
							break;
						}
					}
					else
					{
						AllTilesInADirection.Last()->GetTileDiagonalLeftDown()->SetIsPossibleMoveLocation(true);  
						AllTilesInADirection.Emplace(AllTilesInADirection.Last()->GetTileDiagonalLeftDown());
					}
				}
				else
				{
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetAllTilesInADirection(StartTile) == nullptr!"))
	}
	return AllTilesInADirection;
}

//ATilePtr& ABoard::GetSingleTileInADirection(ATilePtr& StartTile, EDirection Direction, bool CanCapture, int NumberOfTilesAway)
//{
//	ATile* Tile = nullptr;
//
//	switch (Direction)
//	{
//	case EDirection::UP:
//		break;
//	case EDirection::DOWN:
//		break;
//	case EDirection::LEFT:
//		break;
//	case EDirection::RIGHT:
//		break;
//	case EDirection::DIARIGHTUP:
//		break;
//	case EDirection::DIARIGHTDOWN:
//		break;
//	case EDirection::DIALEFTUP:
//		break;
//	case EDirection::DIALEFTDOWN:
//		break;
//	default:
//		break;
//	}
//
//	return Tile;
//}