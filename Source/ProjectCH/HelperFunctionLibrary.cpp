// Fill out your copyright notice in the Description page of Project Settings.

#include "HelperFunctionLibrary.h"

UHelperFunctionLibrary::UHelperFunctionLibrary(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer) {

}

void UHelperFunctionLibrary::DealDamage(UObject* WorldContextObject, AMunition* sourceActor, AActor* hitActor) {
	UHealthComponent* health = Cast<UHealthComponent>(hitActor->GetComponentByClass(UHealthComponent::StaticClass()));
	AShield* shield = Cast<AShield>(hitActor);
	if (health) {
		health->DealDamage(sourceActor->GetDamage());
		APlayerShip* player = Cast<APlayerShip>(hitActor);
		if (player) {
			player->ResetNoDamageMultiplier();
		}
	}
	if (shield) {
		shield->ShieldHit(sourceActor);
	}
}

float UHelperFunctionLibrary::CalculateScore(AShip* destroyedShip, float additionalMultiplier) {
	float shipScore = destroyedShip->GetScoreMultiplier() * destroyedShip->GetBaseScore();
	return shipScore * additionalMultiplier;
}

FTimeComponents UHelperFunctionLibrary::GameTimeToTime(float GameTime) {
	FTimeComponents time;
	time.minutes = floor(GameTime / 60);
	time.seconds = floor(GameTime - time.minutes*60);
	time.milliseconds = floor(fmod(GameTime, 1) * 1000);
	return time;
}

AShip* UHelperFunctionLibrary::FindNearestEnemy(UObject* WorldContextObject) {
	UWorld* World = Cast<UWorld>(WorldContextObject);
	APawn* playerShip = World->GetFirstPlayerController()->GetPawn();
	if (!playerShip) {
		UE_LOG(LogTemp, Error, TEXT("Cannot find player ship from world"), )
		return nullptr;
	}

	AShip* target = nullptr;
	float minDistance = INT32_MAX;
	for (TActorIterator<AShip> EnemyItr(World); EnemyItr; ++EnemyItr) {
		AShip* ship = *EnemyItr;
		if (ship == playerShip) continue;
		float distance = ship->GetDistanceTo(playerShip);
		if (distance < minDistance) {
			minDistance = distance;
			target = ship;
		}
	}
	return target;
}