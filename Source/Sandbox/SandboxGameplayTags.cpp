#include "SandboxGameplayTags.h"

namespace SandboxGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_BlockInput, "State.BlockInput", "Blocks all player movement and look input.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_BlockMovement, "State.BlockMovement", "Blocks player movement while allowing camera look.");
}