// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"           
#include "EnhancedInputComponent.h"
#include "BlasterCharacter.generated.h"


UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = Camera,meta=(AllowPrivateAccess=true))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera,meta=(AllowPrivateAccess=true))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input,meta=(AllowPrivateAccess=true))
	class UInputMappingContext* PlayerInputMapping;

	UPROPERTY(EditAnywhere, Category = Input,meta=(AllowPrivateAccess=true))
	class UInputAction* PlayerMove;

	UPROPERTY(EditAnywhere, Category = Input,meta=(AllowPrivateAccess=true))
	class UInputAction* PlayerLook;

	UPROPERTY(EditAnywhere, Category = Input,meta=(AllowPrivateAccess=true))
	class UInputAction* PlayerJump;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
};
