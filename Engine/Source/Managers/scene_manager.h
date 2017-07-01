#pragma once

// User-defined Headers
#include "shader_manager.h"
#include "model_manager.h"
#include "camera_manager.h"
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

		/**
		 * Returns pointer to internal model manager
		 * @return Pointer to internal model manager object
		 */
		Managers::ModelManager* GetModelManager();

		/**
		* Set shader manager of the scene manager
		* @param Pointer to the shader manager
		*/
		void SetShaderManager(Managers::ShaderManager*& shader_manager);

		/**
		* Set model manager of the scene manager
		* @param Pointer to the model manager
		*/
		void SetModelManager(Managers::ModelManager*& model_manager);

		/**
		* Set camera manager of the scene manager
		* @param Pointer to the camera manager
		*/
		void SetCameraManager(Managers::CameraManager*& camera_manager);

	private:

		/* SceneManager contains a shader manager */
		Managers::ShaderManager* shader_manager_;

		/* SceneManager also contains a model manager */
		Managers::ModelManager* model_manager_;

		/* SceneManager has a CameraManager to take care of view and projection matrices */
		Managers::CameraManager* camera_manager_;
	};
}