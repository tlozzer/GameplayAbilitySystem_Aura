// Copyright Luma Studios


#include "Character/AuraEnemyCharacter.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AAuraEnemyCharacter::HighlightActor()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.f, 16, FColor::Red, false, 2.f);
}

void AAuraEnemyCharacter::UnhighlightActor()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 50.f, 16, FColor::Blue, false, 2.f);
}
