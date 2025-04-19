#include "Mover.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

// Constructor: Enables ticking for this component
UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("[UMover] ERROR: Owner is NULL!"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("[UMover] SUCCESS: Mover is attached to %s"), *Owner->GetName());
	OriginalLocation = GetOwner()->GetActorLocation();
}

// Called every frame to handle movement logic
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
	FVector TargetLocation = OriginalLocation;
	if (ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffSet;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffSet.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	UE_LOG(LogTemp, Warning, TEXT("Moving from %s to %s"), *CurrentLocation.ToString(), *NewLocation.ToString());
    
	GetOwner()->SetActorLocation(NewLocation);
}

// Sets whether the object should move or not
void UMover::SetShouldMove(bool bMove)
{
	ShouldMove = bMove;
	UE_LOG(LogTemp, Warning, TEXT("SetShouldMove: %s"), ShouldMove ? TEXT("True") : TEXT("False"));
}
