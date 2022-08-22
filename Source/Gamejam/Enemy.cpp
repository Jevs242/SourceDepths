// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>("Root Component");
	SpriteComp = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite Component");
	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere Component");

	SetRootComponent(RootComponent);
	SpriteComp->SetupAttachment(RootComponent);
	SphereComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &AEnemy::FDestroy, 10.0f);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	Location.X +=  Speed * DeltaTime;

	SetActorLocation(Location);

}

void AEnemy::FBite()
{
	SpriteComp->SetFlipbook(Sprites[this->NumberEnemy]);
}

void AEnemy::FDestroy()
{
	if (DeathFish)
	{
		SpawnBlood();
	}
	Destroy();
}

void AEnemy::DelayDestroy()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::FDestroy, 0.1, false);
}

void AEnemy::DelayBite()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::FBite, .3, false);
}

void AEnemy::SpawnBlood()
{
	FOutputDeviceNull ar;
	this->CallFunctionByNameWithArguments(TEXT("BiteFish"), ar, NULL, true);
}

