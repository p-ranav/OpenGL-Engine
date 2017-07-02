#pragma once
#include <map>
#include "shader_manager.h"
#include "../Rendering/object.h"
#include "../Rendering/Models/triangle.h"
#include "../Rendering/Models/quad.h"

namespace Managers
{
	/**
	 * ModelManager Class contains an internal map of Objects keyed by name
	 */
	class ModelManager
	{
	public:

		/**
		 * ModelManager Default Constructor
		 */
		ModelManager();

		/**
		* ModelManager Default Destructor
		*/
		~ModelManager();

		/**
		 * This method calls the Draw() methods of each Object in 
		 * the manager's internal map
		 */
		void Draw();

		/**
		* Every renderable object has a Draw call that takes a camera object as input
		* @param camera object which has the projection_matrix and the view matrix
		*/
		void Draw(Managers::CameraManager* camera);

		/**
		* This method calls the Update() methods of each Object in
		* the manager's internal map
		*/
		void Update();

		/**
		* This method deletes a 2D model in the internal map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel2D(const std::string& model_name);

		/**
		* This method fetches a 2D model from the internal map
		* @param model_name Name of the model to fetch
		* @return Constant Reference to the model fetched from the internal map
		*/
		const Rendering::ObjectInterface& GetModel2D(const std::string& model_name) const;

		/**
		* This method deletes a 3D model in the internal map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel3D(const std::string& model_name);

		/**
		* This method fetches a 3D model from the internal map
		* @param model_name Name of the model to fetch
		* @return Constant Reference to the model fetched from the internal map
		*/
		const Rendering::ObjectInterface& GetModel3D(const std::string& model_name) const;

		/**
		* Adds a new 2D model to the model map
		* @param model_name Name of the model
		* @param object Pointer to the object to store
		*/
		void AddModel2D(const std::string& model_name, Rendering::ObjectInterface* object);

		/**
		 * Adds a new 3D model to the model map
		 * @param model_name Name of the model
		 * @param object Pointer to the object to store
		 */
		void AddModel3D(const std::string& model_name, Rendering::ObjectInterface* object);

	private:

		/** 
		 * Internal map of 2D models 
		 * Key: Model Name
		 * Value: Model Object
		 */
		std::map<std::string, Rendering::ObjectInterface*> model_map_2d_;

		/**
		* Internal map of 3D models
		* Key: Model Name
		* Value: Model Object
		*/
		std::map<std::string, Rendering::ObjectInterface*> model_map_3d_;
	};
}