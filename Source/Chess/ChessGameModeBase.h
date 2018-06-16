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

	class ABoard* GetGameBoard() { return GameBoard; }

private:
	AChessGameModeBase();

	virtual	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Board = nullptr;

	class ABoard* GameBoard = nullptr;
	
	
};
