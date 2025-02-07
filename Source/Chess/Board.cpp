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

TArray<ATile*>& ABoard::GetAllTilesUp(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileUp())
	{
		if (!StartingTile->GetTileUp()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileUp());
		} 
		else
		{
			if (StartingTile->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileUp()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileUp());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp())
		{
			if (!StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
			}
			else
			{
				if (StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp()->GetTileUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}
	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesDown(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileDown())
	{
		if (!StartingTile->GetTileDown()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileDown());
		}
		else
		{
			if (StartingTile->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileDown()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileDown());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown())
		{
			if (!StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
			}
			else
			{
				if (StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown()->GetTileDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}
	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesLeft(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileLeft())
	{
		if (!StartingTile->GetTileLeft()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileLeft());
		}
		else
		{
			if (StartingTile->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileLeft()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileLeft());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft())
		{
			if (!StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
			}
			else
			{
				if (StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft()->GetTileLeft());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesRight(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileRight())
	{
		if (!StartingTile->GetTileRight()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileRight());
		}
		else
		{
			if (StartingTile->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileRight()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileRight());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight())
		{
			if (!StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
			}
			else
			{
				if (StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight()->GetTileRight());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesDiagonalRightUp(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileDiagonalRightUp())
	{
		if (!StartingTile->GetTileDiagonalRightUp()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp());
		}
		else
		{
			if (StartingTile->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp())
		{
			if (!StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp()->GetTileDiagonalRightUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesDiagonalRightDown(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileDiagonalRightDown())
	{
		if (!StartingTile->GetTileDiagonalRightDown()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown());
		}
		else
		{
			if (StartingTile->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown())
		{
			if (!StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown()->GetTileDiagonalRightDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesDiagonalLeftUp(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileDiagonalLeftUp())
	{
		if (!StartingTile->GetTileDiagonalLeftUp()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp());
		}
		else
		{
			if (StartingTile->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp())
		{
			if (!StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp()->GetTileDiagonalLeftUp());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}

TArray<ATile*>& ABoard::GetAllTilesDiagonalLeftDown(ATile*& StartingTile)
{
	TilesToReturn.Empty();

	if (StartingTile->GetChessPiece() == nullptr) { UE_LOG(LogTemp, Error, TEXT("GetAllTiles%->GetChessPiece() NULL ERROR"))return TilesToReturn; }

	if (StartingTile->GetTileDiagonalLeftDown())
	{
		if (!StartingTile->GetTileDiagonalLeftDown()->GetHasChessPiece())
		{
			TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown());
		}
		else
		{
			if (StartingTile->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
			{
				StartingTile->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown());
				return TilesToReturn;
			}
			else
			{
				return TilesToReturn;
			}
		}
		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}

		if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown())
		{
			if (!StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetHasChessPiece())
			{
				TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
			}
			else
			{
				if (StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetChessPiece()->GetIsWhite() != StartingTile->GetChessPiece()->GetIsWhite())
				{
					StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->SetIsPossibleCaptureLocation(true);
					TilesToReturn.Add(StartingTile->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown()->GetTileDiagonalLeftDown());
					return TilesToReturn;
				}
				else
				{
					return TilesToReturn;
				}
			}
		}
		else
		{
			return TilesToReturn;
		}
	}

	return TilesToReturn;
}
