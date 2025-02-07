// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class AChessPiece;
class ATile;

typedef AChessPiece* AChessPiecePtr;
typedef ATile* ATilePtr;

enum class EDirection 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIARIGHTUP,
	DIARIGHTDOWN,
	DIALEFTUP,
	DIALEFTDOWN
};

UCLASS()
class CHESS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:
	void SetDarkMaterial();

	void SetLightMaterial();

	void SetPossibleMoveMaterial();

	void SetHighlightedPossibleMoveMaterial();

	void SetPossibleCaptureMaterial();

	void SetHighlightedPossibleCaptureMaterial();

	void SetDefaultMaterial();

	bool GetIfLightMaterial() { return (bIsLightMaterial ? true : false); }

	void SetName(FName NewName) { TileName = NewName; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetTileName() { return TileName; }

	bool GetHasChessPiece();

	void SetChessPice(AChessPiecePtr NewChessPiece) { CurrentChessPiece = NewChessPiece; }

	AChessPiecePtr& GetChessPiece() {
		if (CurrentChessPiece) { return CurrentChessPiece; }
		else { /*UE_LOG(LogTemp, Warning, TEXT("Returning RootChessPiece instead"))*/ return RootChessPiece; }
	}

	void SetIsPossibleMoveLocation(bool Value) { bIsPossibleMoveLocation = Value; }

	bool GetIsPossibleMoveLocation() { return bIsPossibleMoveLocation; }

	void SetIsPossibleCaptureLocation(bool Value) { bIsPossibleCaptureLocation = Value; }
	
	bool GetIsPossibleCaptureLocation() { return bIsPossibleCaptureLocation; }

	TArray<ATilePtr>& GetAllTilesInADirection(ATilePtr& StartTile, EDirection Direction, class ABoard*& Gameboard);

	void SetTileUp(ATilePtr TileIn) { TileUp = TileIn; }
	void SetTileDown(ATilePtr TileIn) { TileDown = TileIn; }
	void SetTileLeft(ATilePtr TileIn) { TileLeft = TileIn; }
	void SetTileRight(ATilePtr TileIn) { TileRight = TileIn; }
	void SetTileDiagonalRightUp(ATilePtr TileIn) { TileDiagonalRightUp = TileIn; }
	void SetTileDiagonalLeftUp(ATilePtr TileIn) { TileDiagonalLeftUp = TileIn; }
	void SetTileDiagonalRightDown(ATilePtr TileIn) { TileDiagonalRightDown = TileIn; }
	void SetTileDiagonalLeftDown(ATilePtr TileIn) { TileDiagonalLeftDown = TileIn; }

	ATilePtr& GetTileUp() { return TileUp; }
	ATilePtr& GetTileDown() { return TileDown; }
	ATilePtr& GetTileLeft() { return TileLeft; }
	ATilePtr& GetTileRight() { return TileRight; }
	ATilePtr& GetTileDiagonalRightUp() { return TileDiagonalRightUp; }
	ATilePtr& GetTileDiagonalLeftUp() { return TileDiagonalLeftUp; }
	ATilePtr& GetTileDiagonalRightDown() { return TileDiagonalRightDown; }
	ATilePtr& GetTileDiagonalLeftDown() { return TileDiagonalLeftDown; }

	UPROPERTY(VisibleAnywhere)
	int index = 0;

	UPROPERTY(VisibleAnywhere)
	FName TileName = "";

	//void SetTempCurrentChessPiece(AChessPiece* ChessPiece) { TempCurrentChessPiece = ChessPiece; }
	void TempAddChessPiece(AChessPiece* ChessPiece) { TempAddedChessPiece = ChessPiece; }
	void SetTempCapturedChessPiece(AChessPiece* ChessPiece) { TempCapturedChessPiece = ChessPiece; }
	void SetTempLastChessPiece(AChessPiece* ChessPiece) { TempLastChessPiece = ChessPiece; }
	void TempRemoveChessPiece(AChessPiece* ChessPiece) { TempRemovedChessPiece = ChessPiece; }

	AChessPiece*& GetTempAddedChessPiece() { return TempAddedChessPiece; }
	AChessPiece*& GetTempRemovedChessPiece() { return TempRemovedChessPiece; }
	AChessPiece*& GetRootChessPiece() { return RootChessPiece; }
	AChessPiece*& GetTempCapturedChessPiece() { return TempCapturedChessPiece; }
	AChessPiece*& GetTempLastChessPiece() { return TempLastChessPiece; }
	//AChessPiece*& GetTempCurrentChessPiece() { return TempCurrentChessPiece; }

	void SetCurrentChessPieceToNull() { CurrentChessPiece = nullptr; }
	//void SetTempCurrentChessPiece() { TempCurrentChessPiece = nullptr; }
	// Sets the root piece to null
	void SetRootPieceToNull() { RootChessPiece = nullptr; }

	// Undos last move on the tile
	void ResetTileToLastState();
	// Reset back to complete root state
	void ResetToRootChessPiece();
	// Set current chess piece as root chess piece
	void SetRootPieceFromCurrentChessPiece();
	// Null all piece pointers
	void SetAllChessPiecePointersToNull();

	void SetAIMovedFromThisTile(bool Value) { bAIMovedFromThisTile = Value; }
	bool GetAIMovedFromThisTile() { return bAIMovedFromThisTile; }
	void SetAIMovedToThisTile(bool Value) { bAIMovedToThisTile = Value; }
	bool GetAIMovedToThisTile() { return bAIMovedToThisTile; }

private:
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* LightMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* DarkMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* PossibleMoveMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* HighlightedPossibleMoveMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* PossibleCaptureMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* HighlightedPossibleCaptureMaterial = nullptr;

	bool bIsLightMaterial = false;
	bool bIsDarkMaterial = false;

	FVector ChessPieceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 20);

	UPROPERTY(VisibleAnywhere)
	bool bIsPossibleMoveLocation = false;

	UPROPERTY(VisibleAnywhere)
	bool bIsPossibleCaptureLocation = false;

	bool bAIMovedFromThisTile = false;

	bool bAIMovedToThisTile = false;

	bool bAICapturedThisTile = false;

	UPROPERTY(VisibleAnywhere)
	AChessPiece* RootChessPiece = nullptr;
	UPROPERTY(VisibleAnywhere)
	AChessPiece* CurrentChessPiece = nullptr;
	//UPROPERTY(VisibleAnywhere)
	//AChessPiece* TempCurrentChessPiece = nullptr;
	UPROPERTY(VisibleAnywhere)
	AChessPiece* TempRemovedChessPiece = nullptr;
	UPROPERTY(VisibleAnywhere)
	AChessPiece* TempAddedChessPiece = nullptr;
	UPROPERTY(VisibleAnywhere)
	AChessPiece* TempCapturedChessPiece = nullptr;
	UPROPERTY(VisibleAnywhere)
	AChessPiece* TempLastChessPiece = nullptr;

	UPROPERTY(VisibleAnywhere)
	ATile* TileUp = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileDown = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileLeft = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileRight = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileDiagonalRightUp = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileDiagonalLeftUp = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileDiagonalRightDown = nullptr;
	UPROPERTY(VisibleAnywhere)
	ATile* TileDiagonalLeftDown = nullptr;

	TArray<ATilePtr> AllTilesInADirection;
};
