// Copyright Luma Studios


#include "Character/AuraEnemyCharacter.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(250);
	GetWeapon()->SetCustomDepthStencilValue(250);
}

void AAuraEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetWeapon()->SetRenderCustomDepth(true);
}

void AAuraEnemyCharacter::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	GetWeapon()->SetRenderCustomDepth(false);
}
