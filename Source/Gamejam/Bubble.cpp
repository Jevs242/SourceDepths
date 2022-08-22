// Fill out your copyright notice in the Description page of Project Settings.


#include "Bubble.h"

// Sets default values
ABubble::ABubble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SetRootComponent(RootComponent);

	SpriteComp->SetupAttachment(RootComponent);

}

// Called every frame
void ABubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	float Move = Location.Z + (DeltaTime * Speed);
	float MoveX = Location.X + (DeltaTime * Speed);


	SetActorLocation(FVector(MoveX, Location.Y, Move));

}

