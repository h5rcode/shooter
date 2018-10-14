#pragma once

namespace Shooter {
	namespace Input {
		typedef enum EventType {
			NOTHING = 0,
			LEFT_BUTTON_CLICKED = 1,
			RIGHT_BUTTON_CLICKED = 2,
			DROP_PROP = 3,
			QUIT = 4
		} EventType;

		class Event
		{
		public:
			Event();

			void setType(EventType type);
			EventType getType() const;

		private:
			EventType _eventType;
		};
	}
}