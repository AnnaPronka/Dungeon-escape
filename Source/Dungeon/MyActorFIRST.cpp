// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorFIRST.h"

// Sets default values
AMyActorFIRST::AMyActorFIRST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActorFIRST::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorFIRST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Display, TEXT("TickComponent is running 5555"));

}

