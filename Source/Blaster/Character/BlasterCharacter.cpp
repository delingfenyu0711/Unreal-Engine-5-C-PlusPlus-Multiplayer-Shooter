
#include "BlasterCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "InputActionValue.h" 
#include "GameFramework/CharacterMovementComponent.h"


ABlasterCharacter::ABlasterCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
}


void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerControl = Cast<APlayerController>(Controller);
	if (PlayerControl)
	{
		UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControl->GetLocalPlayer());
		if (LocalPlayerSubsystem)
		{
			LocalPlayerSubsystem->AddMappingContext(PlayerInputMapping,0);

		}

		PlayerControl->PlayerCameraManager->ViewPitchMax = 10.f;
		PlayerControl->PlayerCameraManager->ViewPitchMin = -30.f;
	}

	
	
}




void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerInput)
	{
		PlayerInput->BindAction(PlayerMove,ETriggerEvent::Triggered,this,&ThisClass::Move);
		PlayerInput->BindAction(PlayerLook,ETriggerEvent::Triggered,this,&ThisClass::Look);
		PlayerInput->BindAction(PlayerJump,ETriggerEvent::Started,this,&ThisClass::Jump);
		PlayerInput->BindAction(PlayerJump,ETriggerEvent::Completed,this,&ThisClass::StopJumping);
		
	}
}

void ABlasterCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D F2d = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YawRotator(0,Rotator.Yaw,0);
		const FVector PlayerForward = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		const FVector PlayerRight = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(PlayerForward,F2d.Y);
		AddMovementInput(PlayerRight,F2d.X);
	}
	
}

void ABlasterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D F2d = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerPitchInput(F2d.Y);
		AddControllerYawInput(F2d.X);
	}
}





