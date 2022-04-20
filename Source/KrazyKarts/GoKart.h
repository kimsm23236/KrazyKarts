// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"


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

USTRUCT()
struct FGoKartState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
	FGoKartMove LastMove;	
};

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

	void ApplyRotation(float DeltaTime, float steeringThrow);

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SimulateMove(FGoKartMove Move);

	FGoKartMove CreateMove(float DeltaTime);
	void ClearAcknowledgedMoves(FGoKartMove LastMove);

	FVector GetAirResistance();
	FVector GetRollingResistance();

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

	void UpdateLocationFromVelocity(float DeltaTime);
	
	void MoveForward(float Value);

	void MoveRight(float Value);


	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendMove(FGoKartMove Move);

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FGoKartState ServerState;

	FVector Velocity;

	UFUNCTION()
		void OnRep_ServerState();

	float Throttle;
	float SteeringThrow;

	TArray<FGoKartMove> UnacknowledgedMoves;
};
