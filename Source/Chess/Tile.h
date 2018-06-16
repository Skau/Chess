// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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

	void SetAllTilesAroundBlue();

	bool GetIfLightMaterial() { return (bIsLightMaterial ? true : false); }

	void SetName(FName NewName) { TileName = NewName; }

	FName GetTileName() { return TileName; }

	bool GetHasChessPiece() { return CurrentChessPiece ? true : false; }

	void SetChessPice(class AChessPiece* NewChessPiece) { CurrentChessPiece = NewChessPiece; }

	class AChessPiece* GetChessPiece() { return CurrentChessPiece; }

	void SetIsPossibleMoveLocation(bool Value) { bIsPossibleMoveLocation = Value; }

	bool GetIsPossibleMoveLocation() { return bIsPossibleMoveLocation; }

	void SetIsPossibleCaptureLocation(bool Value) { bIsPossibleCaptureLocation = Value; }
	
	bool GetIsPossibleCaptureLocation() { return bIsPossibleCaptureLocation; }

	FVector GetChessPieceLocation() { UE_LOG(LogTemp, Warning, TEXT("%s"), *ChessPieceLocation.ToString()) return ChessPieceLocation; }

	int GetRow() { return Row; }

	void SetRow(int RowIn) { Row = RowIn; }

	TArray<ATile*>& GetAllTilesInADirection(ATile* StartTile, EDirection Direction);

	ATile* GetSingleTile(ATile* StartTile, EDirection Direction, int NumberOfTilesAway);

	void SetTileUp(ATile* TileIn) { TileUp = TileIn; }
	void SetTileDown(ATile* TileIn) { TileDown = TileIn; }
	void SetTileLeft(ATile* TileIn) { TileLeft = TileIn; }
	void SetTileRight(ATile* TileIn) { TileRight = TileIn; }
	void SetTileDiagonalRightUp(ATile* TileIn) { TileDiagonalRightUp = TileIn; }
	void SetTileDiagonalLeftUp(ATile* TileIn) { TileDiagonalLeftUp = TileIn; }
	void SetTileDiagonalRightDown(ATile* TileIn) { TileDiagonalRightDown = TileIn; }
	void SetTileDiagonalLeftDown(ATile* TileIn) { TileDiagonalLeftDown = TileIn; }

	ATile* GetTileUp() { return TileUp; }
	ATile* GetTileDown() { return TileDown; }
	ATile* GetTileLeft() { return TileLeft; }
	ATile* GetTileRight() { return TileRight; }
	ATile* GetTileDiagonalRightUp() { return TileDiagonalRightUp; }
	ATile* GetTileDiagonalLeftUp() { return TileDiagonalLeftUp; }
	ATile* GetTileDiagonalRightDown() { return TileDiagonalRightDown; }
	ATile* GetTileDiagonalLeftDown() { return TileDiagonalLeftDown; }

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

	FName TileName;

	AChessPiece* CurrentChessPiece = nullptr;

	FVector ChessPieceLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 20);

	bool bIsPossibleMoveLocation = false;

	bool bIsPossibleCaptureLocation = false;

	int Row = 0;

	ATile* TileUp = nullptr;
	ATile* TileDown = nullptr;
	ATile* TileLeft = nullptr;
	ATile* TileRight = nullptr;
	ATile* TileDiagonalRightUp = nullptr;
	ATile* TileDiagonalLeftUp = nullptr;
	ATile* TileDiagonalRightDown = nullptr;
	ATile* TileDiagonalLeftDown = nullptr;

	TArray<ATile*> AllTilesInADirection;

};
