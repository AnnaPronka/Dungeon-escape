#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEON_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMover();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool bMove);

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffSet = FVector(0.0f, 0.0f, -600.0f);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime = 4.0f;

	bool ShouldMove = false;

	FVector OriginalLocation;
};
