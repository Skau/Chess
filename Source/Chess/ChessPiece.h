// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

class ATile;

enum class EDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class CHESS_API AChessPiece : public AActor
{
	GENERATED_BODY()
	
public:

	void SetWhiteMaterial();

	void SetWhiteMaterialHighlighted();

	void SetBlackMaterial();

	void SetblackMaterialHighlighted();

	void SetDefaultMaterial();

	bool GetIsWhite() { return bIsWhite; }

	FName GetCurrentTileName();

	ATile* GetCurrentTile() { return CurrentTile; }

	void SetCurrentTile(ATile* NewTile) { CurrentTile = NewTile; }

	virtual TArray<ATile*>& GetAllPossibleTiles();

	void MoveToNewTile(ATile * NewTile, bool WillCapturePiece = false);

protected:
	// Sets default values for this actor's properties
	AChessPiece();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* WhiteMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* BlackMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* BlackMaterialHighlighted = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* WhiteMaterialHighlighted = nullptr;

	bool bIsWhite = false;

	ATile* CurrentTile = nullptr;

	TArray<ATile*> AllPossibleTiles;

	class AChessGameModeBase* GameMode = nullptr;

	class ABoard* GameBoard = nullptr;

	bool bIsFirstMove = true;
};
