// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class ATile;
class ABoard;
class AChessPiece;

typedef ATile* ATilePtr;
typedef ABoard* ABoardPtr;
typedef AChessPiece* AChessPiecePtr;

UCLASS()
class CHESS_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:
	TArray<ATile*>& GetAllTiles() { return Tiles; }

	TArray<ATile*>& GetAllTilesUp(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesDown(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesLeft(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesRight(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalRightUp(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalRightDown(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalLeftUp(ATile*& StartingTile);
	TArray<ATile*>& GetAllTilesDiagonalLeftDown(ATile*& StartingTile);

	void SpawnChessPieces();

	void SpawnChessPiecesTemp(ABoard*& GameBoard, class AChessPiece* ChessPieceToCopy, ATile* TileToSpawnOn);

	TArray<class AChessPiece*>& GetAllWhitePieces() { return AllWhitePieces; }

	TArray<class AChessPiece*>& GetAllBlackPieces() { return AllBlackPieces; }

	void UpdateChessPiecesLeft(class AChessPiece* ChessPieceToRemove, bool IfWhite);

	void UpdateTilePointers();

	ABoard* CreateTempGameBoard();

	void DestroyBoard();

	void SaveCurrentChessPieces(bool IsRoot);

	void ResetAllChessPiecesToLastState();

	void RootUndo();

private:
	// Sets default values for this actor's properties
	ABoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTiles(bool bIsTemp);

	void SpawnChessPiece(ABoard*& GameBoard, class AChessPiece* ChessPieceToCopy, ATile* TileToSpawnOn);

	ATile* GetTileByName(FName Tilename);

	class AChessGameModeBase* GameMode = nullptr;

	class AChessAI* ChessAI = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

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

	TArray<AChessPiece*> AllBlackPieces;

	TArray<AChessPiece*> AllWhitePieces;

	TArray<ATile*> Tiles;

	TArray<ATile*> TilesToReturn;

	TArray<AChessPiece*> ChessPieces;

	FVector CursorWorldLocation = FVector(0);
};
