// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ChessGameModeBase.h"
#include "Board.h"
#include "ChessPiece.h"

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

	if (bIsPossibleCaptureLocation)
	{
		bIsPossibleCaptureLocation = false;
	}

	if (bIsPossibleMoveLocation)
	{
		bIsPossibleMoveLocation = false;
	}
}

bool ATile::GetHasChessPiece()
{
	bool Bool = false;

	if (CurrentChessPiece)
	{
		Bool = true;
	}
	//else if (RootChessPiece)
	//{
	//	/*UE_LOG(LogTemp, Warning, TEXT("RootChessPiece = true!"))*/
	//	Bool = true;
	//}

	return Bool;
}

void ATile::SetDarkMaterial()
{
	if (DarkMaterial && Mesh->GetMaterial(0) != DarkMaterial)
	{
		Mesh->SetMaterial(0, DarkMaterial);
		bIsDarkMaterial = true;
	}
}

// Undos last move on the tile
void ATile::ResetTileToLastState()
{
	// If any new piece was moved here, remove the piece
	if (TempAddedChessPiece)
	{
		CurrentChessPiece = nullptr;
		TempAddedChessPiece = nullptr;
	}

	// If a piece was captured here, put the captured piece back
	if (TempCapturedChessPiece)
	{
		CurrentChessPiece = TempCapturedChessPiece;
		TempCapturedChessPiece = nullptr;
	}

	// If any piece moved away from here, put it back
	if (TempRemovedChessPiece)
	{
		if (TempRemovedChessPiece != CurrentChessPiece)
		{
			CurrentChessPiece = TempRemovedChessPiece;
		}
		TempRemovedChessPiece = nullptr;
	}

}

// Reset back to complete root state
void ATile::ResetToRootChessPiece()
{
	// null all pointers and set the root piece as current piece

	if (TempAddedChessPiece)
	{
		TempAddedChessPiece = nullptr;
	}

	if (TempRemovedChessPiece)
	{
		TempRemovedChessPiece = nullptr;
	}

	if (TempCapturedChessPiece)
	{
		TempCapturedChessPiece = nullptr;
	}

	CurrentChessPiece = RootChessPiece;
	//RootChessPiece = CurrentChessPiece;
}

// Set current chess piece as root chess piece
void ATile::SetRootPieceFromCurrentChessPiece()
{
	RootChessPiece = CurrentChessPiece;
}

// Null all piece pointers
void ATile::SetAllChessPiecePointersToNull()
{
	CurrentChessPiece = nullptr;
	RootChessPiece = nullptr;
	TempAddedChessPiece = nullptr;
	TempRemovedChessPiece = nullptr;
	TempCapturedChessPiece = nullptr;
}
