// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

class ATile;

UENUM(BlueprintType)
enum class EPieceType : uint8
{
	Pawn,
	Rook,
	Knight,
	Bishop,
	King,
	Queen,
	None
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsWhite() { return bIsWhite; }
	
	FName GetCurrentTileName();

	ATile*& GetCurrentTile() { return CurrentTile; }

	void SetCurrentTile(ATile* NewTile) { CurrentTile = NewTile; }

	virtual TArray<ATile*>& GetAllPossibleTiles();

	void MoveToNewTile(ATile*& NewTile);

	void AI_TestMove(ATile*& NewTile, class ABoard*& GameBoard);
	
	void AI_UndoTestMove(ATile*& OldTile, class ABoard*& GameBoard, AChessPiece*& CapturedPawn);

	void SetPieceType(EPieceType PieceType) { Type = PieceType; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EPieceType GetPieceType() { return Type; }

	int GetMaterialValue() { return MaterialValue; }

	virtual ~AChessPiece() = default;
protected:
	// Sets default values for this actor's properties
	AChessPiece();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

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

	class AChessAI* ChessAI = nullptr;

	UPROPERTY(VisibleAnywhere)
	ATile* CurrentTile = nullptr;

	TArray<ATile*> AllPossibleTiles;

	class AChessGameModeBase* GameMode = nullptr;

	class ABoard* GameBoard = nullptr;

	bool bIsFirstMove = true;

	EPieceType Type = EPieceType::None;

	int MaterialValue = 0;
};
