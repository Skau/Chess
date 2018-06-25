// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "PawnPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API APawnPiece : public AChessPiece
{
	GENERATED_BODY()
	
public:

private:

	APawnPiece();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual TArray<ATile*>& GetAllPossibleTiles(class ABoard*& GameBoard) override;
	
};
