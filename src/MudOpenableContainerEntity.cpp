#include <MudOpenableContainerEntity.h>
#include <MudAction.h>

namespace Mud {

	OpenableContainerEntity::OpenableContainerEntity(const char *name, const char *entityTemplateName)
		: ContainerEntity(name, entityTemplateName) {

		state = OCS_IDLE;
		isOpen = false;

		openAnimationState = entity->getAnimationState("Open");
		openAnimationState->setLoop(false);
		openAnimationState->setEnabled(true);
	}
	OpenableContainerEntity::~OpenableContainerEntity() {
	}

	void OpenableContainerEntity::Update() {
		if (state == OCS_OPENING) {
			openAnimationState->addTime(1.0/60.0);
			if (openAnimationState->getTimePosition() >= openAnimationState->getLength()) {
				state = OCS_IDLE;
				isOpen = true;
			}
		}
		else if (state == OCS_CLOSING) {
			openAnimationState->addTime(-1.0/60.0);
			if (openAnimationState->getTimePosition() <= 0.0) {
				state = OCS_IDLE;
				isOpen = false;
			}
		}

		SceneryEntity::Update();
	}

	void OpenableContainerEntity::SetPosition(Ogre::Vector3 pos) {
		ContainerEntity::SetPosition(pos);
	}
	void OpenableContainerEntity::UpdatePosition() {
		ContainerEntity::UpdatePosition();
	}

	void OpenableContainerEntity::StartOpening() {
		if (state == OCS_IDLE) {
			state = OCS_OPENING;
		}
	}

	void OpenableContainerEntity::StartClosing() {
		if (state == OCS_IDLE) {
			state = OCS_CLOSING;
		}
	}

	void OpenableContainerEntity::ToggleState() {
		if (isOpen) {
			StartClosing();
		} else {
			StartOpening();
		}
	}


	void OpenableContainerEntity::ActionPerform(Action *action) {
		switch (action->type) {
			case(AT_DEFAULT):
				break;
			case(AT_TOGGLE_CONTAINER_STATE):
			{
				if (isOpen || !isLocked) {
					ToggleState();
				}
				break;
			}
		}
	}

	ActionType OpenableContainerEntity::GetDefaultActionType() {
		return AT_TOGGLE_CONTAINER_STATE;
	}

}
