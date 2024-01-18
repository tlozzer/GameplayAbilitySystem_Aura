// Copyright Luma Studios


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 120.f;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");

}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
