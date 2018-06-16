// Fill out your copyright notice in the Description page of Project Settings.

#include "Board.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Tile.h"
#include "PawnPiece.h"

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
						TileToUpdate->SetTileDown(Tiles[i + 1]);
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
						TileToUpdate->SetTileUp(Tiles[i - 1]);
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