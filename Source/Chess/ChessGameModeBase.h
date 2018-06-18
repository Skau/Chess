// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AChessGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class ABoard* GetGameBoard() { return GameBoard; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsWhiteTurn() { return bIsWhiteTurn; }

	void SetGameIsOver(bool DidWhiteWin) { bGameIsOver = true; bWhiteWon = DidWhiteWin; }

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIfGameIsOver() { return bGameIsOver; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetWhiteWon() { return bWhiteWon; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetGameIsActive() { return bGameIsActive; }

	UFUNCTION(BlueprintCallable)
	void SetGameIsActive(bool Value) { bGameIsActive = Value; }

	void ToggleTurn();

	void IncrementBlackPawnsLost() { BlackPawnsLost++; }
	void IncrementBlackRooksLost() { BlackRooksLost++; }
	void IncrementBlackKnightsLost() { BlackKnightsLost++; }
	void IncrementBlackBishopsLost() { BlackBishopsLost++; }
	void SetBlackQueenLost() { BlackQueenLost = 1; }
	void IncrementWhitePawnsLost() { WhitePawnsLost++; }
	void IncrementWhiteRooksLost() { WhiteRooksLost++; }
	void IncrementWhiteKnightsLost() { WhiteKnightsLost++; }
	void IncrementWhiteBishopsLost() { WhiteBishopsLost++; }
	void SetWhiteQueenLost() { WhiteQueenLost = 1; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlackPawnsLost() { return BlackPawnsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlackRooksLost() { return BlackRooksLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlackKnightsLost() { return BlackKnightsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlackBishopsLost() { return BlackBishopsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetBlackQueenLost() { return BlackQueenLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetWhitePawnsLost() { return WhitePawnsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetWhiteRooksLost() { return WhiteRooksLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetWhiteKnightsLost() { return WhiteKnightsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetWhiteBishopsLost() { return WhiteBishopsLost; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetWhiteQueenLost() { return WhiteQueenLost; }

private:
	AChessGameModeBase();

	virtual	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Board = nullptr;

	class ABoard* GameBoard = nullptr;
	
	bool bIsWhiteTurn = true;

	bool bGameIsOver = false;

	bool bWhiteWon = false;

	bool bGameIsActive = false;

	int BlackPawnsLost = 0;
	int BlackRooksLost = 0;
	int BlackKnightsLost = 0;
	int BlackBishopsLost = 0;
	int BlackQueenLost = 0;
	int WhitePawnsLost = 0;
	int WhiteRooksLost = 0;
	int WhiteKnightsLost = 0;
	int WhiteBishopsLost = 0;
	int WhiteQueenLost = 0;
};
