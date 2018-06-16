// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Tile.h"
#include "PawnPiece.h"
#include "KnightPiece.h"
#include "BishopPiece.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	WhitePawnsTakenMesh = CreateDefaultSubobject<UStaticMeshComponent>("WhitePawnsTakenMesh");
	WhitePawnsTakenMesh->SetupAttachment(RootComponent);

	BlackPawnsTakenMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlackPawnsTakenMesh");
	BlackPawnsTakenMesh->SetupAttachment(RootComponent);

	Tiles.Reserve(64);
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnTiles();


}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::SpawnTiles()
{
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
					SpawnLocation.X = 43.75;
					SpawnLocation.Y -= 12.5;
				}
				else if (!bUseLightMaterial)
				{
					Tile->SetLightMaterial();
					SpawnLocation.X = 43.75;
					SpawnLocation.Y -= 12.5;
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
			Tile->SetName(FName(*(FString("Tile") + FString::FromInt(i))));
			Tile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Tiles.Add(Tile);

			FVector SpawnLocation = FVector(0);

			if (i < 16)
			{
				if (i == 0)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<AKnightPiece>(
						KnightPiece, SpawnLocation, FRotator(0));
					piece->SetWhiteMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 2)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<ABishopPiece>(
						BishopPiece, SpawnLocation, FRotator(0));
					piece->SetWhiteMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 5)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<ABishopPiece>(
						BishopPiece, SpawnLocation, FRotator(0));
					piece->SetWhiteMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 7)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<AKnightPiece>(
						KnightPiece, SpawnLocation, FRotator(0));
					piece->SetWhiteMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (PawnPiece && i <= 15 && i >= 8)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<APawnPiece>(
						PawnPiece, SpawnLocation, FRotator(0));
					piece->SetWhiteMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);

					//ChessPieces.Add(piece);
				}
			}
			else if (i > 47)
			{
				if (i == 63)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<AKnightPiece>(
						KnightPiece, SpawnLocation, FRotator(0));
					piece->SetBlackMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 61)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<ABishopPiece>(
						BishopPiece, SpawnLocation, FRotator(0));
					piece->SetBlackMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 58)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<ABishopPiece>(
						BishopPiece, SpawnLocation, FRotator(0));
					piece->SetBlackMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (i == 56)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<AKnightPiece>(
						KnightPiece, SpawnLocation, FRotator(0));
					piece->SetBlackMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);
				}

				if (PawnPiece && i <= 55 && i >= 48)
				{
					SpawnLocation = FVector(Tiles[i]->GetActorLocation().X, Tiles[i]->GetActorLocation().Y, 20);
					auto piece = GetWorld()->SpawnActor<APawnPiece>(
						PawnPiece, SpawnLocation, FRotator(0));
					piece->SetBlackMaterial();

					piece->SetCurrentTile(Tile);
					Tile->SetChessPice(piece);

					//ChessPieces.Add(piece);
				}
			}
		}

		if (Tiles.Num())
		{
			for (int i = 0; i < 64; ++i)
			{
				if (i + 1 >= 0 && i + 1 <= 63)
				{
					if (Tiles[i + 1])
					{
						Tiles[i]->SetTileDown(Tiles[i + 1]);
					}
				}
				if (i - 1 >= 0 && i - 1 <= 63)
				{
					if (Tiles[i - 1])
					{
						Tiles[i]->SetTileUp(Tiles[i - 1]);
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
				if (i + 9 >= 0 && i + 9 <= 63)
				{
					if (Tiles[i + 9])
					{
						Tiles[i]->SetTileDiagonalLeftDown(Tiles[i + 9]);
					}
				}
				if (i - 9 >= 0 && i - 9 <= 63)
				{
					if (Tiles[i - 9])
					{
						Tiles[i]->SetTileDiagonalRightDown(Tiles[i - 9]);
					}
				}
				if (i + 7 >= 0 && i + 7 <= 63)
				{
					if (Tiles[i + 7])
					{
						Tiles[i]->SetTileDiagonalLeftUp(Tiles[i + 7]);
					}
				}
				if (i - 7 >= 0 && i - 7 <= 63)
				{
					if (Tiles[i - 7])
					{
						Tiles[i]->SetTileDiagonalRightUp(Tiles[i - 7]);
					}
				}
			}
		}
	}
}

void ABoard::SetTileRows()
{
	int index = 0;
	for (auto& Tile : Tiles)
	{
		if (index >= 0 && index <= 8)
		{
			Tile->SetRow(1);
		}
		else if (index >= 9 && index <= 16)
		{
			Tile->SetRow(2);
		}
		else if (index >= 17 && index <= 24)
		{
			Tile->SetRow(3);
		}
		else if (index >= 25 && index <= 32)
		{
			Tile->SetRow(4);
		}
		else if (index >= 33 && index <= 40)
		{
			Tile->SetRow(5);
		}
		else if (index >= 41 && index <= 48)
		{
			Tile->SetRow(6);
		}
		else if (index >= 49 && index <= 56)
		{
			Tile->SetRow(7);
		}
		else if (index >= 57 && index <= 63)
		{
			Tile->SetRow(8);
		}
	}
}

void ABoard::CapturePiece(AChessPiece * PieceCaptured)
{
	if (PieceCaptured)
	{
		PieceCaptured->Destroy();
	}
}

ATile* ABoard::GetTileUnderCursor(FVector CursorLocation)
{
	ATile* TileToReturn = nullptr;
	return TileToReturn;
}

void ABoard::UpdateTilesForTile(ATile* TileToUpdate)
{
	if (Tiles.Num())
	{
		for (int i = 0; i <= 63; ++i)
		{
			if (Tiles[i] == TileToUpdate)
			{
				if (i + 1 >= 0 && i + 1<= 63)
				{
					if (Tiles[i + 1])
					{
						if (TileToUpdate->GetTileDown())
						{
							TileToUpdate->GetTileDown()->SetDefaultMaterial();
						}
						if ((i % 7 == 0 || i % 8 == 0) && i != 0)
						{
							TileToUpdate->SetTileDown(nullptr);
						}
						else
						{
							TileToUpdate->SetTileDown(Tiles[i + 1]);
						}
					}
				}
				if (i - 1 >= 0 && i - 1 <= 63)
				{
					if (Tiles[i - 1])
					{
						if (TileToUpdate->GetTileUp())
						{
							TileToUpdate->GetTileUp()->SetDefaultMaterial();
						}
						if ((i % 7 == 0 || i % 8 == 0) && i != 0)
						{
							TileToUpdate->SetTileUp(nullptr);
						}
						else
						{
							TileToUpdate->SetTileUp(Tiles[i - 1]);
						}
					}
				}
				if (i + 8 >= 0 && i + 8 <= 63)
				{
					if (Tiles[i + 8])
					{
						if (TileToUpdate->GetTileLeft())
						{
							TileToUpdate->GetTileLeft()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileLeft(Tiles[i + 8]);
					}
				}
				if (i - 8 >= 0 && i - 8 <= 63)
				{
					if (Tiles[i - 8])
					{
						if (TileToUpdate->GetTileRight())
						{
							TileToUpdate->GetTileRight()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileRight(Tiles[i - 8]);
					}
				}
				if (i + 9 >= 0 && i + 9 <= 63)
				{
					if (Tiles[i + 9])
					{
						if (TileToUpdate->GetTileDiagonalLeftDown())
						{
							TileToUpdate->GetTileDiagonalLeftDown()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileDiagonalLeftDown(Tiles[i + 9]);
					}
				}
				if (i - 9 >= 0 && i - 9 <= 63)
				{
					if (Tiles[i - 9])
					{
						if (TileToUpdate->GetTileDiagonalRightDown())
						{
							TileToUpdate->GetTileDiagonalRightDown()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileDiagonalRightDown(Tiles[i - 9]);
					}
				}
				if (i + 7 >= 0 && i + 7 <= 63)
				{
					if (Tiles[i + 7])
					{
						if (TileToUpdate->GetTileDiagonalLeftUp())
						{
							TileToUpdate->GetTileDiagonalLeftUp()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileDiagonalLeftUp(Tiles[i + 7]);
					}
				}
				if (i - 7 >= 0 && i - 7 <= 63)
				{
					if (Tiles[i - 7])
					{
						if (TileToUpdate->GetTileDiagonalRightUp())
						{
							TileToUpdate->GetTileDiagonalRightUp()->SetDefaultMaterial();
						}
						TileToUpdate->SetTileDiagonalRightUp(Tiles[i - 7]);
					}
				}
			}
		}
	}
}

TArray<ATile*>& ABoard::GetAllTilesUp(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesDown(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesLeft(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesRight(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesDiagonalRightUp(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesDiagonalRightDown(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesDiagonalLeftUp(ATile* StartingTile)
{
	TilesToReturn.Empty();

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

TArray<ATile*>& ABoard::GetAllTilesDiagonalLeftDown(ATile* StartingTile)
{
	TilesToReturn.Empty();

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