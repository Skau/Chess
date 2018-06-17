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

	UFUNCTION(BlueprintCallable)
	void StartGame();

	void SetGameIsOver(bool DidWhiteWin) { bGameIsOver = true; bWhiteWon = DidWhiteWin; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIfGameIsOver() { return bGameIsOver; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetWhiteWon() { return bWhiteWon; }

	void ToggleTurn();

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
};
