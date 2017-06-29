#pragma once
namespace Core {

	/**
	 * Listener Interface between InitGLUT and SceneManager
	 */
	class ListenerInterface
	{
	public:

		// Pure Virtual Destructor
		virtual ~ListenerInterface() = 0;

		// Display Functions
		virtual void NotifyBeginFrame() = 0;
		virtual void NotifyDisplayFrame() = 0;
		virtual void NotifyEndFrame() = 0;
		virtual void NotifyReshape(int width, int height, int previous_width, int previous_height) = 0;
	};

	// Implementation of Pure Virtual Destructor
	inline ListenerInterface::~ListenerInterface() {}
}