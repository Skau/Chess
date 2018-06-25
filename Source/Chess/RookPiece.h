// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "RookPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ARookPiece : public AChessPiece
{
	GENERATED_BODY()

	void BeginPlay() override;
	
	virtual TArray<ATile*>& GetAllPossibleTiles(class ABoard*& Gameboard) override;

	TArray<ATile*> PossibleTilesToMove;
	
};
