#include <events/MudCharacterClosedContainerEvent.h>
#include <MudContainerEntity.h>
#include <MudCharacterEntity.h>
#include <MudCore.h>

namespace Mud {

	CharacterClosedContainerEvent::CharacterClosedContainerEvent(CharacterEntity *_character, OpenableContainerEntity *_container)
		: Event() {
		character = _character;
		container = _container;
	}

	CharacterClosedContainerEvent::~CharacterClosedContainerEvent() {
	}

	void CharacterClosedContainerEvent::Update() {
		if (fabs((character->node->getPosition()-container->node->getPosition()).normalisedCopy().getRotationTo(
						container->node->getOrientation() * Ogre::Vector3::UNIT_Z).getYaw().valueDegrees()) < container->accessAngle) {

		}
		Finish();
	}

}
