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

	TArray<FMove> FindAllPossibleMoves(ABoard*& GameBoard);
};
