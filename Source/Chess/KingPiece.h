// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "KingPiece.generated.h"

/**
 * 
 */
UCLASS()
class CHESS_API AKingPiece : public AChessPiece
{
	GENERATED_BODY()

	void BeginPlay() override;

	virtual TArray<ATile*>& GetAllPossibleTiles(class ABoard*& GameBoard) override;

	TArray<ATile*> PossibleTilesToMove;
	
	
};
