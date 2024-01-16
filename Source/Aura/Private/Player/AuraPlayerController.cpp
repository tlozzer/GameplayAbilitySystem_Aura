// Copyright Luma Studios


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D NormalizedInputAxisVector = Value.Get<FVector2D>().GetSafeNormal();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	
	const FRotationMatrix RotationMatrix(YawRotation);
	const FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardVector, NormalizedInputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightVector, NormalizedInputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit))
	{
		LastActor = CurrentActor;
		CurrentActor = Cast<IEnemyInterface>(CursorHit.GetActor());

		if (LastActor == nullptr) 
		{
			if (CurrentActor != nullptr)
			{
				// LastActor is null and CurrentActor is valid -> Highlight CurrentActor
				CurrentActor->HighlightActor();
			}
		}
		else // LastActor is valid
		{
			if (CurrentActor == nullptr)
			{
				// LastActor is valid and CurrentActor is null -> Unhighlight LastActor
				LastActor->UnhighlightActor();
			}
			else // Both actors are valid
			{
				if (LastActor != CurrentActor)
				{
					// Both actor are valid, but LastActor != CurrentActor -> Unhighlight LastActor and highlight CurrentActor
					LastActor->UnhighlightActor();
					CurrentActor->HighlightActor();
				}
			}
		}
	}
}
