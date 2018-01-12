// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

#define OUT

UCLASS(Blueprintable)
class PROJECTCH_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveLeft();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveRight();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveUp();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void MoveDown();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveLeft();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveRight();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveUp();
	UFUNCTION(BlueprintCallable, Category = "ShipMovement")
	void StopMoveDown();
	UFUNCTION(BlueprintCallable, Category = "ShipScore")
	float GetBaseScore() const;
	UFUNCTION(BlueprintCallable, Category = "ShipScore")
	float GetScoreMultiplier() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	float movementSpeed;
	UPROPERTY(EditAnywhere)
	FVector upDirection = FVector::UpVector;
	UPROPERTY(EditAnywhere)
	FVector downDirection = -FVector::UpVector;
	UPROPERTY(EditAnywhere)
	FVector leftDirection = -FVector::RightVector;
	UPROPERTY(EditAnywhere)
	FVector rightDirection = FVector::RightVector;
	UPROPERTY(EditDefaultsOnly)
	float baseScore = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float maxMultiplier = 2.0f;
	UPROPERTY(EditDefaultsOnly)
	float decayTime = 5.0f;
	UPROPERTY(VisibleInstanceOnly)
	float currentMultiplier; 
	UPROPERTY(VisibleInstanceOnly)
	float decayPerSecond;
	FVector currentMovement = FVector::ZeroVector;
	void Initialize();
	void NormalizeMovementVectors();
	void DecayMultiplier(float DeltaTime);
};
