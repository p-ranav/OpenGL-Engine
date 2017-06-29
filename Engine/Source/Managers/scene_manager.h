#pragma once

// User-defined Headers
#include "shader_manager.h"
#include "model_manager.h"
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
	
		/**
		 * Calls every model's update
		 */
		virtual void NotifyBeginFrame();

		/**
		 * Sets up OpenGL bits and calls every model's draw
		 */
		virtual void NotifyDisplayFrame();

		/**
		* Post-draw operations on all models
		*/
		virtual void NotifyEndFrame();

		/**
		 * Calls every model's reshape handler
		 * @param width New window width
		 * @param height New window height
		 * @param previous_width Previous window width
		 * @param previous_height Previous window height
		 */
		virtual void NotifyReshape(int width, int height, int previous_width, int previous_height);

	private:

		/* SceneManager contains a shader manager */
		Managers::ShaderManager* shader_manager_;

		/* SceneManager also contains a model manager */
		Managers::ModelManager* model_manager_;
	};
}