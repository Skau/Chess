// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class AChessPiece* GetCurrentChessPieceClicked() { return CurrentChessPieceClicked; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AChessPiece* GetCurrentChessPieceHovered() { return CurrentChessPieceHovered; }

private:
	ACustomPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void OnHover();

	void OnLeftClick();

	void ResetHoveringChessPiece();

	void UpdateHoveringChessPiece();

	void ResetHoveringTile();

	void UpdateHoveringTile();

	void ResetSelectedChessPieceTiles(class AChessPiece* ChessPiece = nullptr);

	void UpdateSelectedChessPieceTiles();
	
	FHitResult CursorHitResult;

	class ATile* CurrentHoveredTile = nullptr;

	class AChessGameModeBase* GameMode = nullptr;

	class ABoard* GameBoard = nullptr;

	class AChessPiece* CurrentChessPieceHovered = nullptr;

	AChessPiece* CurrentChessPieceClicked = nullptr;

	TArray<ATile*> CurrentPossibleMoveLocationTiles;

	bool bPieceIsCapturing = false;
	
};
