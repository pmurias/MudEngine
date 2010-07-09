#include <events/MudCharacterOpenedContainerEvent.h>
#include <MudContainerEntity.h>
#include <MudCharacterEntity.h>
#include <MudCore.h>

namespace Mud {

	CharacterOpenedContainerEvent::CharacterOpenedContainerEvent(CharacterEntity *_character, OpenableContainerEntity *_container)
		: Event() {
		character = _character;
		container = _container;
	}

	CharacterOpenedContainerEvent::~CharacterOpenedContainerEvent() {
	}

	void CharacterOpenedContainerEvent::Update() {
		if (fabs((character->node->getPosition()-container->node->getPosition()).normalisedCopy().getRotationTo(
								container->node->getOrientation() * Ogre::Vector3::UNIT_Z).getYaw().valueDegrees()) < container->accessAngle) {

		}
		Finish();
	}

}
