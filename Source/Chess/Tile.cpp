// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameModeBase.h"
#include "Board.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetLightMaterial()
{
	if (LightMaterial && Mesh->GetMaterial(0) != LightMaterial)
	{
		Mesh->SetMaterial(0, LightMaterial);
		bIsLightMaterial = true;
	}

}

void ATile::SetPossibleMoveMaterial()
{
	if (PossibleMoveMaterial && Mesh->GetMaterial(0) != PossibleMoveMaterial)
	{
		Mesh->SetMaterial(0, PossibleMoveMaterial);
	}
}

void ATile::SetHighlightedPossibleMoveMaterial()
{
	if (HighlightedPossibleMoveMaterial && Mesh->GetMaterial(0) != HighlightedPossibleMoveMaterial)
	{
		Mesh->SetMaterial(0, HighlightedPossibleMoveMaterial);
	}
}

void ATile::SetPossibleCaptureMaterial()
{
	if (PossibleCaptureMaterial && Mesh->GetMaterial(0) != PossibleCaptureMaterial)
	{
		Mesh->SetMaterial(0, PossibleCaptureMaterial);
	}
}

void ATile::SetHighlightedPossibleCaptureMaterial()
{
	if (HighlightedPossibleCaptureMaterial && Mesh->GetMaterial(0) != HighlightedPossibleCaptureMaterial)
	{
		Mesh->SetMaterial(0, HighlightedPossibleCaptureMaterial);
	}
}

void ATile::SetDefaultMaterial()
{
	if (bIsLightMaterial)
	{
		SetLightMaterial();
	}
	else
	{
		SetDarkMaterial();
	}
}

void ATile::SetAllTilesAroundBlue()
{
	if (TileUp)
	{
		TileUp->SetPossibleMoveMaterial();
	}
	if (TileDown)
	{
		TileDown->SetPossibleMoveMaterial();
	}
	if (TileLeft)
	{
		TileLeft->SetPossibleMoveMaterial();
	}
	if (TileRight)
	{
		TileRight->SetPossibleMoveMaterial();
	}
	if (TileDiagonalRightUp)
	{
		TileDiagonalRightUp->SetPossibleMoveMaterial();
	}
	if (TileDiagonalLeftUp)
	{
		TileDiagonalLeftUp->SetPossibleMoveMaterial();
	}
	if (TileDiagonalRightDown)
	{
		TileDiagonalRightDown->SetPossibleMoveMaterial();
	}
	if (TileDiagonalLeftDown)
	{
		TileDiagonalLeftDown->SetPossibleMoveMaterial();
	}
}

void ATile::SetDarkMaterial()
{
	if (DarkMaterial && Mesh->GetMaterial(0) != DarkMaterial)
	{
		Mesh->SetMaterial(0, DarkMaterial);
		bIsDarkMaterial = true;
	}
}

TArray<ATile*>& ATile::GetAllTilesInADirection(ATile * StartTile, EDirection Direction)
{
	AllTilesInADirection.Empty();

	auto GameMode = Cast<AChessGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto GameBoard = GameMode->GetGameBoard();

	switch (Direction)
	{
	case EDirection::UP:
		for (auto& TileToAdd : GameBoard->GetAllTilesUp(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::DOWN:
		for (auto& TileToAdd : GameBoard->GetAllTilesDown(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::LEFT:
		for (auto& TileToAdd : GameBoard->GetAllTilesLeft(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::RIGHT:
		for (auto& TileToAdd : GameBoard->GetAllTilesRight(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::DIARIGHTUP:
		for (auto& TileToAdd : GameBoard->GetAllTilesDiagonalRightUp(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::DIARIGHTDOWN:
		for (auto& TileToAdd : GameBoard->GetAllTilesDiagonalRightDown(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::DIALEFTUP:
		for (auto& TileToAdd : GameBoard->GetAllTilesDiagonalLeftUp(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	case EDirection::DIALEFTDOWN:
		for (auto& TileToAdd : GameBoard->GetAllTilesDiagonalLeftDown(StartTile))
		{
			AllTilesInADirection.Add(TileToAdd);
		}
		break;
	default:
		break;
	}
	

	return AllTilesInADirection;
}

ATile* ATile::GetSingleTile(ATile * StartTile, EDirection Direction, int NumberOfTilesAway)
{
	ATile* TileToReturn = nullptr;

	return TileToReturn;
}