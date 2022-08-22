// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn.h"

// Sets default values
ASpawn::ASpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	RootComponent = GetRootComponent();
	BoxComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, AShark::StaticClass(), ReturnedActors);
	MainShark = nullptr;
	if (ReturnedActors.Num() > 0)
	{
		MainShark = Cast<AShark>(ReturnedActors[0]);
	}

	FTimerHandle SpawnHandle;
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ASpawn::Spawn, 3.0f, true , .1f);
}

// Called every frame
void ASpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawn::Spawn()
{ 
	if (MainShark)
	{
		if (MainShark->DoStarted && !MainShark->IsDead)
		{

			for (int i = 0; i < MainShark->getCounterRounds() + 7 ; i++)
			{
				FVector WorldLoc = BoxComp->GetComponentLocation();
				FVector BoxExtent = BoxComp->GetScaledBoxExtent();
				FVector RandomLoc;
				

				if (!FirstTime)
				{
					RandomLoc = UKismetMathLibrary::RandomPointInBoundingBox(WorldLoc, BoxExtent);
					FirstTime = true;
				}
				else
				{

					while (true)
					{
						RandomLoc = UKismetMathLibrary::RandomPointInBoundingBox(WorldLoc, BoxExtent);
						FVector FDistance = RandomLoc - PreviosLocation;
						float Distance = FDistance.Size();
						if (Distance > 500)
						{
							break;
						}
					}

				}
				PreviosLocation = RandomLoc;
				
				AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(BP_Enemy, RandomLoc, FRotator(0, 0, 0));
				if (Enemy)
				{
					while (true)
					{
						Enemy->NumberEnemy = FMath::RandRange(0, 2);
						if (Enemy->NumberEnemy != PreviosNumber)
						{
							break;
						}
					}
					PreviosNumber = Enemy->NumberEnemy;

					Enemy->SpriteComp->SetFlipbook(Enemy->Sprites[Enemy->NumberEnemy]);
					
					int Color;
					int Trash;
					if (MainShark->getCounterRounds() == 5 && MainShark->getPercentContamination() == 1 && i == 5)
					{
						Enemy->NumberEnemy = 0;
					}
					switch (Enemy->NumberEnemy)
					{
					case 0:
						
						while (true)
						{
							Color = FMath::RandRange(0, 4);
							if (PreviosColor != Color)
							{
								break;
							}
						}

						
						PreviosColor = Color;
						
						Enemy->SpriteComp->SetFlipbook(Enemy->ColorFish[Color]);
						Enemy->SphereComp->SetSphereRadius(105.f);
						Enemy->SetActorScale3D(FVector(0.15, 0.15, 0.15));
						break;
					case 1:
						Enemy->SphereComp->SetSphereRadius(30.f);
						Enemy->SetActorScale3D(FVector(-0.40, -0.40, 0.40));
						break;
					case 2:

						while (true)
						{
							Trash = FMath::RandRange(0, 5);
							if (PreviosTrash != Trash)
							{
								break;
							}
						}

						PreviosTrash = Trash;

						Enemy->SpriteComp->SetFlipbook(Enemy->NumberTrash[Trash]);
						Enemy->SphereComp->SetSphereRadius(25.f);
						Enemy->SetActorScale3D(FVector(0.10, 0.10, 0.10));
						break;
					default:
						break;
					}
					
					switch (Enemy->NumberEnemy)
					{
					case 0:
						Enemy->Speed = FMath::RandRange(300, 600);
						break;
					case 1:
						Enemy->Speed = FMath::RandRange(400, 650);
						break;
					case 2:
						Enemy->Speed = FMath::RandRange(300, 500);
						break;
					default:
						break;
					}

				}
			}
		}
	}
}

