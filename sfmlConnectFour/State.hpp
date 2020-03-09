#pragma once


//Aesel is just a unique name for reference (donkey in Danish)
namespace Aesel {
	class State {
	public:
		virtual void Init() = 0;

		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0; //dt is delta time, the time between frames, so whether animations need to be drawn or not can be calculated

		virtual void Pause() { }
		virtual void Resume() { }
	};
}
