#pragma once

// User-defined Headers
#include "..\Core\Init\init_glut.h"
#include "..\Rendering\Texture\texture_loader.h"
#include "scene_manager.h"

namespace Managers
{
	/**
	 * Primary Engine Interface to be used to setup scenes
	 */
	class EngineManager
	{
	public:

		/**
		 * EngineManager Default Constructor
		 */
		EngineManager();

		/**
		* EngineManager Default Destructor
		*/
		~EngineManager();

		/**
		 * Initializes OpenGL context and all the managers
		 */
		bool Init();

		/**
		 * Engine's main run method
		 * Calls InitGLUT::Run()
		 */
		void Run();

		/**
		 * Return engine's scene manager
		 * @return scene manager
		 */
		Managers::SceneManager*  GetSceneManager()  const;

		/**
		* Return engine's shader manager
		* @return shader manager
		*/
		Managers::ShaderManager* GetShaderManager() const;

		/**
		* Return engine's model manager
		* @return model manager
		*/
		Managers::ModelManager* GetModelManager() const;

		/**
		* Return engine's camera manager
		* @return camera manager
		*/
		Managers::CameraManager* GetCameraManager() const;

		/**
		 * Return engine's texture loader object
		 * @return texture loader
		 */
		Rendering::TextureLoader* GetTextureLoader() const;

	private:

		/* Engine's main Scene manager object */
		Managers::SceneManager*  scene_manager_;

		/* Engine's main Shader Manager - Same one set in Scene manager */
		Managers::ShaderManager* shader_manager_;

		/* Engine's main Model Manager - Same one set in Scene manager */
		Managers::ModelManager* model_manager_;

		/* Engine's main Camera Manager - Same one set in Scene manager */
		Managers::CameraManager* camera_manager_;

		/* Engine's texture loader object */
		Rendering::TextureLoader* texture_loader_;
	};
}