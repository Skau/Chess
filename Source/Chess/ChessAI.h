// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessAI.generated.h"

class AChessPiece;
class ATile;
class ABoard;
class AChessGameModeBase;

USTRUCT(immutable, noexport, BlueprintType)
struct FMove
{
	UPROPERTY()
	AChessPiece* ChessPiece = nullptr;

	UPROPERTY()
	ATile* PossibleTileToMove = nullptr;

	UPROPERTY()
	int Value = 0;

	FMove()
	{
		ChessPiece = nullptr;
		PossibleTileToMove = nullptr;
		Value = 0;
	}

	FMove(FMove*& Move)
	{
		ChessPiece = Move->ChessPiece;
		PossibleTileToMove = Move->PossibleTileToMove;
		Value = Move->Value;
	}

	FMove(AChessPiece*& ChessPieceToAdd, ATile*& TileToAdd, int ValueToAdd = 0)
	{
		ChessPiece = ChessPieceToAdd;
		PossibleTileToMove = TileToAdd;
		Value = ValueToAdd;
	}
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

	void MovePiece(FMove*& Move, ABoard*& Gameboard);
private:
	AChessGameModeBase* GameMode = nullptr;

	FMove* MiniMaxRoot(ABoard*& Gameboard, int depth, bool IsMaximisingPlayer);

	int Minimax(ABoard*& Gameboard, int depth, int Alpha, int Beta, bool IsMaximisingPlayer);

	TArray<FMove*>& FindAllPossibleMoves(ABoard*& GameBoard, bool IsMaximisingPlayer);

	int EvaluateBoard(ABoard*& GameBoard);

	void Undo(FMove*& Move, ABoard*& Gameboard);

	int TotalNumberOfBoardEvaluates = 0;

	TArray<ABoard*> AllTempBoards;

	TArray<ATile*> SavedTiles;

	TArray<FMove*> PossibleTilesToMove;
};
