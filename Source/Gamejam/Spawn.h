// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"

#include "Enemy.h"
#include "Shark.h"

#include "Spawn.generated.h"

UCLASS()
class GAMEJAM_API ASpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComp;

private:

	UPROPERTY(EditAnywhere , Category = "Object")
		TSubclassOf<AEnemy> BP_Enemy;

	UPROPERTY(EditAnywhere, Category = "Object")
		TSubclassOf<AShark> BP_Shark;

	void Spawn();

	AShark* MainShark;

	int PreviosNumber = -1;
	int PreviosColor = -1;
	int PreviosTrash = -1;
	FVector PreviosLocation;

	bool FirstTime;
};
