// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlasterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UBlasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	
protected:

	
private:
	UPROPERTY(BlueprintReadOnly,Category=Character,meta=(AllowPrivateAccess=true))
	class ABlasterCharacter* BlasterCharacter;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Character,meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Character,meta=(AllowPrivateAccess=true))
	bool bIsAir;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Character,meta=(AllowPrivateAccess=true))
	bool bIsAccelerating;
	
	
};
