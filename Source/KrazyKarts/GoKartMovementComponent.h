// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"


USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float Throttle;
	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;
	UPROPERTY()
		float Time;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	// Getter, Setter
	FVector GetVelocity() { return Velocity; }
	void SetVelocity(FVector Val) { Velocity = Val; }

	float GetThrottle() { return Throttle; }
	void SetThrottle(float Val) { Throttle = Val; }

	float GetSteeringThrow() { return SteeringThrow; }
	void SetSteeringThrow(float Val) { SteeringThrow = Val; }

	FGoKartMove GetLastMove() { return LastMove; }

private:

	FGoKartMove CreateMove(float DeltaTime);

	void ApplyRotation(float DeltaTime, float steeringThrow);

	FVector GetAirResistance();
	FVector GetRollingResistance();

	void UpdateLocationFromVelocity(float DeltaTime);

	// 자동차의 질량 (kg)
	UPROPERTY(EditAnywhere)
		float Mass = 1000;

	// 스로틀이 완전히 내려갔을 때 차에 가해지는 힘
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	// 완전히 돌린 상태에서 자동차 회전 반경의 최소 반지름(m)
	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10;

	// 높을수력 더 많은 항력
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;

	// 높을수력 더 많은 구름 항력
	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = 0.015f;

	FVector Velocity;

	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;
};
