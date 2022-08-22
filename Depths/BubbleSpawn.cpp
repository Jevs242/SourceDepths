// Fill out your copyright notice in the Description page of Project Settings.


#include "BubbleSpawn.h"

// Sets default values
ABubbleSpawn::ABubbleSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Component"));
	DestroyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Destroy Component"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SetRootComponent(RootComponent);
	DestroyBox->SetupAttachment(RootComponent);
	SpawnBox->SetupAttachment(RootComponent);

	DestroyBox->OnComponentBeginOverlap.AddDynamic(this, &ABubbleSpawn::BeginOverlap);
}

// Called when the game starts or when spawned
void ABubbleSpawn::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SpawnTimer;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ABubbleSpawn::SpawnBubble, 1.0f, true, 0.0f);

}

// Called every frame
void ABubbleSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABubbleSpawn::SpawnBubble()
{
	FVector WorldLoc = SpawnBox->GetComponentLocation();
	FVector BoxExtent = SpawnBox->GetScaledBoxExtent();
	FVector RandomLoc = UKismetMathLibrary::RandomPointInBoundingBox(WorldLoc, BoxExtent);

	for (int i = 0; i < 25; i++)
	{
		RandomLoc = UKismetMathLibrary::RandomPointInBoundingBox(WorldLoc, BoxExtent);
		float Random = FMath::RandRange(0.5, 1.0);

		FTransform Transform = FTransform(FRotator(0,0,0), RandomLoc, FVector(Random, Random, Random));

		ABubble* Bubble = GetWorld()->SpawnActor<ABubble>(BP_Bubble, Transform);
	}
}

void ABubbleSpawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABubble* Bubble = Cast<ABubble>(OtherActor);
	if (Bubble)
	{
		Bubble->Destroy();
	}
}

