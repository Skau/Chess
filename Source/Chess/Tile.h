// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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
	
};
