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

	virtual TArray<ATile*>& GetAllPossibleTiles(class ABoard*& Gameboard);

	void MoveToNewTile(ATile*& NewTile, class ABoard*& Gameboard);

	void AI_TestMove(ATile*& NewTile, class ABoard*& GameBoard);
	
	void AI_UndoTestMove(struct FMove*& Move, class ABoard *& GameBoard, bool IsLastRegularUndo);

	void SetPieceType(EPieceType PieceType) { Type = PieceType; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EPieceType GetPieceType() { return Type; }

	int GetMaterialValue() { return MaterialValue; }

	void SetRootTileToCurrentTile() { RootTile = CurrentTile; }

	void SetCurrentTileToRootTile() { if (RootTile) { CurrentTile = RootTile; } }

	ATile*& GetCurrentRootTile() { return RootTile; }

	ATile*& GetLastTile() { return LastTiles.Last(); }

	TArray<ATile*>& GetAllLastTiles() { return LastTiles; }

	void EmptyAllLastTiles() { LastTiles.Empty(); }

	void SetCurrentTileToLastTile() { if (LastTiles.Num())CurrentTile = LastTiles.Pop(); }

	void SetLastTileToCurrentTile() { LastTiles.Push(CurrentTile); }

	virtual ~AChessPiece() = default;

	void SetHasTempFirstMoved() { bHasTempFirstMoved = true; }

	void ResetHasTempFirstMoved() { bHasTempFirstMoved = false; }

	bool GetHasFirstTempMoved() { return bHasTempFirstMoved; }

	bool GetHasFirstMoved() { return bIsFirstMove; }

	void SetFirstMove(bool Value) { bIsFirstMove = Value; }

	void FixTilesAtEndOfRound();

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

	UPROPERTY(VisibleAnywhere)
	TArray<ATile*> LastTiles;

	UPROPERTY(VisibleAnywhere)
	ATile* RootTile = nullptr;

	UPROPERTY(VisibleAnywhere)
	ATile* LastTile = nullptr;

	TArray<ATile*> AllPossibleTiles;

	class AChessGameModeBase* GameMode = nullptr;

	class ABoard* GameBoard = nullptr;

	bool bIsFirstMove = true;

	EPieceType Type = EPieceType::None;

	int MaterialValue = 0;

	bool bHasTempFirstMoved = false;
};
