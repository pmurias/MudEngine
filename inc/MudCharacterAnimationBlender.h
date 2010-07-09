#ifndef _MudCharacterAnimationBlender
#define _MudCharacterAnimationBlender

#include <OGRE/Ogre.h>
#include <MudEnums.h>

namespace Mud {

	class CharacterEntity;

	class CharacterAnimationBlender {
	public:
		Ogre::AnimationState *animStates[CAS_COUNT];
		bool animEnabled[CAS_COUNT];
		float animTrans[CAS_COUNT];
		float animSpeeds[CAS_COUNT];

		CharacterAnimationBlender(CharacterEntity *character);

		void SetAnimation(CharacterAnimationState as, float trans=0.15f);
		void SetLoop(CharacterAnimationState as, bool loop);
		float GetTimePosition(CharacterAnimationState as);
		void SetTimePosition(CharacterAnimationState as, float tp);
		float GetLength(CharacterAnimationState as);
		void SetSpeed(CharacterAnimationState as, float speed);
		void SetEnabled(CharacterAnimationState, bool enabled);

		void Update();
	};
}

#endif
