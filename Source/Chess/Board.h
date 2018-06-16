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

	ATile* GetTileUnderCursor(FVector CursorLocation);

	TArray<ATile*>& GetAllTiles() { return Tiles; }

	void CapturePiece(class AChessPiece* PieceCaptured);

	void UpdateTilesForTile(ATile* TileToUpdate);

private:
	// Sets default values for this actor's properties
	ABoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTiles();

	void SetTileRows();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WhitePawnsTakenMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BlackPawnsTakenMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TileActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> PawnPiece;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChessPiece> KnightPiece;

	TArray<ATile*> Tiles;

	TArray<AChessPiece*> ChessPieces;

	FVector CursorWorldLocation = FVector(0);
	
};
