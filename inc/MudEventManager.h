#ifndef _MudEventManager
#define _MudEventManager

#include <deque>

namespace Mud {

	class Event;

	/**
	 * Class used for all game events management
	 */
	class EventManager {
	public:

		std::deque<Event*> events;

		/// Queues new event
		void QueueEvent(Event *e);

		/// Performs behavior based on events
		void UpdateEvents();
	};
}

#endif
