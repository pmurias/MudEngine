#ifndef _MudEvent
#define _MudEvent

namespace Mud {

	/**
	 * Abstract class used for game event representation
	 */
	class Event {
	public:

		/// True if event has finished and is ready to destroy
		bool finished;

		Event();
		virtual ~Event();

		/// Sets finished to true
		void Finish();

		/// Updates event state, possibility to Finish()
		virtual void Update();
	};

}

#endif
