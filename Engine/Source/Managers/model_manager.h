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
		* This method calls the Update() methods of each Object in
		* the manager's internal map
		*/
		void Update();

		/**
		* This method deletes a model in the internal map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel(const std::string& model_name);

		/**
		* This method fetches a model from the internal map
		* @param model_name Name of the model to fetch
		* @return Constant Reference to the model fetched from the internal map
		*/
		const Rendering::ObjectInterface& GetModel(const std::string& model_name) const;

	private:

		/** 
		 * Internal map of models 
		 * Key: Model Name
		 * Value: Model Object
		 */
		std::map<std::string, Rendering::ObjectInterface*> model_map_;
	};
}