// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessAI.generated.h"

class AChessPiece;
class ATile;
class ABoard;
class AChessGameModeBase;

USTRUCT()
struct FMove
{
	GENERATED_BODY()

	AChessPiece* ChessPiece = nullptr;
	ATile* PossibleTileToMove = nullptr;
	int Value = 0;
};

UCLASS()
class CHESS_API AChessAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessAI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartRound(ABoard*& GameBoard);

	void MovePiece(FMove& Move);
private:
	AChessGameModeBase* GameMode = nullptr;

	FMove CalculateBestMove(ABoard*& Gameboard, FMove& Move, int depth);

	FMove MiniMaxRoot(ABoard*& Gameboard, int depth, bool IsMaximisingPlayer);

	int Minimax(ABoard*& Gameboard, int depth, bool IsMaximisingPlayer);

	TArray<FMove> FindAllPossibleMoves(ABoard*& GameBoard);

	int EvaluateBoard(ABoard*& GameBoard);
};
