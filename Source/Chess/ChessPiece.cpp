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
TArray<ATile*>& AChessPiece::GetAllPossibleTiles()
{
	AllPossibleTiles.Empty();
	return AllPossibleTiles;
}

void AChessPiece::MoveToNewTile(ATile*& NewTile)
{
	if (!NewTile || !CurrentTile) {return; }

	if (NewTile->GetIsPossibleMoveLocation())
	{
		if (NewTile->GetIsPossibleCaptureLocation())
		{
			if (GameMode)
			{
				GameMode->GetGameBoard()->UpdateChessPiecesLeft(NewTile->GetChessPiece(), NewTile->GetChessPiece()->GetIsWhite());
			}
			NewTile->GetChessPiece()->Destroy();
		}
		CurrentTile->SetChessPice(nullptr);

		CurrentTile = NewTile;

		SetActorLocation(FVector(CurrentTile->GetActorLocation().X, CurrentTile->GetActorLocation().Y, 20));

		CurrentTile->SetChessPice(this);
		if (bIsFirstMove)
		{
			bIsFirstMove = false;
		}
	}
}

int AChessPiece::AI_TestMove(ATile *& NewTile, ABoard*& GameBoard)
{
	if (!NewTile || !CurrentTile) { return 0; }

	if (NewTile->GetIsPossibleMoveLocation())
	{
		if (NewTile->GetIsPossibleCaptureLocation())
		{
			GameBoard->UpdateChessPiecesLeft(NewTile->GetChessPiece(), NewTile->GetChessPiece()->GetIsWhite());

			NewTile->GetChessPiece()->Destroy();
		}
		CurrentTile->SetChessPice(nullptr);

		CurrentTile = NewTile;

		SetActorLocation(FVector(CurrentTile->GetActorLocation().X, CurrentTile->GetActorLocation().Y, 20));

		CurrentTile->SetChessPice(this);
	}

	//if (NewTile->GetIsPossibleMoveLocation())
	//{
	//	if (NewTile->GetIsPossibleCaptureLocation())
	//	{
	//		MaterialValue = NewTile->GetChessPiece()->GetMaterialValue();
	//	}
	//}

	return MaterialValue;
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
