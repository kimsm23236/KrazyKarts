// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyRotation(float DeltaTime);

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetResistance();

	// 자동차의 질량 (kg)
	UPROPERTY(EditAnywhere)
		float Mass = 1000;

	// 스로틀이 완전히 내려갔을 때 차에 가해지는 힘
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 90;

	// 높을수력 더 많은 항력
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;

	void UpdateLocationFromVelocity(float DeltaTime);

	void MoveForward(float Value);
	void MoveRight(float Value);

	FVector Velocity;

	float Throttle;
	float SteeringThrow;
};
