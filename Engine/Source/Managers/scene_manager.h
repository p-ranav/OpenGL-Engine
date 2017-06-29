/*
* Author: Pranav Srinivas Kumar
*/

#pragma once

// User-defined Headers
#include "shader_manager.h"
#include "../Core/Init/listener.h"
namespace Managers
{
	/**
	 * SceneManager Class
	 * Override Notification Methods
	 */
	class SceneManager : public Core::ListenerInterface
	{
	public:
		/* SceneManager Default Constructor */
		SceneManager();

		/* SceneManager Default Destructor */
		~SceneManager();
	
		// Display Functions
		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previous_width, int previous_height);

	private:

		/* SceneManager contains a shader manager */
		Managers::ShaderManager* shader_manager_;
	};
}