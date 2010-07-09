#include <MudEventManager.h>
#include <events/MudEvent.h>
#include <cstdio>

namespace Mud {

	void EventManager::QueueEvent(Event *e) {
		events.push_back(e);
	}

	void EventManager::UpdateEvents() {
		for (std::deque<Event*>::iterator it = events.begin(); it != events.end(); it++) {
			Event *e = *it;
			e->Update();

			if (e->finished) {
				delete e;
				it = events.erase(it);
				it--;
			}
		}
	}
}
