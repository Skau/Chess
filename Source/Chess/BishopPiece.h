// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "BishopPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API ABishopPiece : public AChessPiece
{
	GENERATED_BODY()

	void BeginPlay() override;

	virtual TArray<ATile*>& GetAllPossibleTiles(class ABoard*& Gameboard, bool IsAI) override;

	TArray<ATile*> PossibleTilesToMove;
	
	
};
