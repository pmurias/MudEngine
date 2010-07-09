#include <MudCharacterAnimationBlender.h>
#include <MudCharacterEntity.h>

namespace Mud {

	CharacterAnimationBlender::CharacterAnimationBlender(CharacterEntity *character)  {
		animStates[CAS_IDLE] = character->entity->getAnimationState("IdleNothing");
		animStates[CAS_RUN_NOTHING] = character->entity->getAnimationState("RunNothing");
		animStates[CAS_PICK] = character->entity->getAnimationState("Pick");
		animStates[CAS_WALK_NOTHING] = character->entity->getAnimationState("WalkNothing");
		animStates[CAS_OPEN_MIDDLE] = character->entity->getAnimationState("OpenMiddle");
		animStates[CAS_CLOSE_MIDDLE] = character->entity->getAnimationState("CloseMiddle");

		for (int i = 0; i < CAS_COUNT; i++) {
			animEnabled[i] = false;
			animTrans[i] = 0.05f;
			animSpeeds[i] = 1.0f;
		}

		SetLoop(CAS_PICK, false);
		SetLoop(CAS_OPEN_MIDDLE, false);
		SetLoop(CAS_CLOSE_MIDDLE, false);
		SetSpeed(CAS_OPEN_MIDDLE, 0.7f);
		SetSpeed(CAS_CLOSE_MIDDLE, 0.7f);
	}

	void CharacterAnimationBlender::SetAnimation(CharacterAnimationState as, float trans) {
		for (int i = 0; i < CAS_COUNT; i++) {
			animEnabled[i] = false;
		}

		animEnabled[as] = true;
		animTrans[as] = trans;
	}

	void CharacterAnimationBlender::SetLoop(CharacterAnimationState as, bool loop) {
		animStates[as]->setLoop(loop);
	}

	float CharacterAnimationBlender::GetTimePosition(CharacterAnimationState as) {
		return animStates[as]->getTimePosition();
	}

	void CharacterAnimationBlender::SetTimePosition(CharacterAnimationState as, float tp) {
		animStates[as]->setTimePosition(tp);
	}

	float CharacterAnimationBlender::GetLength(CharacterAnimationState as) {
		return animStates[as]->getLength();
	}

	void CharacterAnimationBlender::SetSpeed(CharacterAnimationState as, float speed) {
		animSpeeds[as] = speed;
	}

	void CharacterAnimationBlender::SetEnabled(CharacterAnimationState as, bool enabled) {
		animEnabled[as] = enabled;
	}

	void CharacterAnimationBlender::Update() {
		for (int i = 0; i< CAS_COUNT; i++) {
			if (animStates[i]->getEnabled()) {
				if (animEnabled[i] == false) {
					float newWeight = animStates[i]->getWeight() - animTrans[i];
					if (newWeight < 0.0f) {
						newWeight = 0.0f;
					} else {
						animStates[i]->addTime( animSpeeds[i]/60.0f );
					}
					animStates[i]->setWeight(0.0f);
				} else {
					animStates[i]->addTime( animSpeeds[i]/60.0f );
					if (animStates[i]->getWeight() < 1.0f) {
						float newWeight = animStates[i]->getWeight() + animTrans[i];
						if (newWeight > 1.0f) {
							newWeight = 1.0f;
						}
						animStates[i]->setWeight(1.0f);
					}
				}
			} else if (animEnabled[i] == true) {
				animStates[i]->setEnabled(true);
			}
		}

	}
}
