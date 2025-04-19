// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

// Constructor: Enables ticking for this component
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame to check for acceptable actors and trigger movement
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr)
	{
		return;
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false); // Disable physics to allow movement
		}
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform); // Attach actor to trigger
		Mover->SetShouldMove(true); // Trigger movement
	}
	else
	{
		Mover->SetShouldMove(false); // Stop movement if no valid actor
	}
}

// Sets the mover reference used to trigger movement
void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

// Returns the first overlapping actor with the correct tag and not currently grabbed
AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	
	for (AActor* Actor : Actors)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Overlapping Actor: %s"), *Actor->GetName());
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			UE_LOG(LogTemp, Warning, TEXT("Acceptable Actor: %s"), *Actor->GetName());
			return Actor;
		}

		UE_LOG(LogTemp, Warning, TEXT("Actor %s - HasAcceptableTag: %s, IsGrabbed: %s"),
			   *Actor->GetName(),
			   HasAcceptableTag ? TEXT("True") : TEXT("False"),
			   IsGrabbed ? TEXT("True") : TEXT("False"));
	}
	UE_LOG(LogTemp, Warning, TEXT("No Acceptable Actor Found"));
	return nullptr;
}
 