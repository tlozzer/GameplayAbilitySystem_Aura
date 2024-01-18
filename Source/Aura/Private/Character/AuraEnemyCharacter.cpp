// Copyright Luma Studios


#include "Character/AuraEnemyCharacter.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetWeapon()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
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

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
