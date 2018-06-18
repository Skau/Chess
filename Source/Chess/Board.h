// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class ATile;

UCLASS()
class CHESS_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:
	TArray<ATile*>& GetAllTiles() { return Tiles; }

	void CapturePiece(class AChessPiece* PieceCaptured);

	TArray<ATile*>& GetAllTilesUp(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesDown(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesLeft(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesRight(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalRightUp(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalRightDown(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalLeftUp(ATile* StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalLeftDown(ATile* StartingTile);

	void SpawnChessPieces();

private:
	// Sets default values for this actor's properties
	ABoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTiles();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TileActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> PawnPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> KnightPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> BishopPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> QueenPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> KingPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> RookPiece;

	TArray<ATile*> Tiles;

	TArray<ATile*> TilesToReturn;

	TArray<AChessPiece*> ChessPieces;

	FVector CursorWorldLocation = FVector(0);
};
