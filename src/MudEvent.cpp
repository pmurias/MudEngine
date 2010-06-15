#include <MudEvent.h>

namespace Mud {

	Event::Event() {
		finished = false;
	}

	Event::~Event() {
	}

	void Event::Finish() {
		finished = true;
	}

	void Event::Update() {
	}
}
