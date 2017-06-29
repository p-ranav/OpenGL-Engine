/*
* Author: Pranav Srinivas Kumar
*/
#pragma once
// User-defined Headers
#include "vertex_format.h"

// External Headers
#include "glew.h"
#include "freeglut.h"

// System Headers
#include <vector>
#include <map>

namespace Models
{
	/**
	 * Model Manager Class
	 * This class contains a model_name:model_struct map
	 * used to create, fetch and triangulate models as needed
	 */
	class ModelManager
	{
	public:

		/**
		 * ModelManager Default Constructor
		 */
		ModelManager() {}

		/**
		* ModelManager Destructor
		*/
		~ModelManager();

		/**
		* Creates a triangle model and saves it under the provided name
		* @param model_name Name of the triangle model
		*/
		void CreateTriangleModel(const std::string& model_name);

		/**
		* Delete a model from the map
		* @param model_name Name of the model to delete
		*/
		void DeleteModel(const std::string& model_name);

		/**
		* Get a model from the model map
		* @param model_name Name of model to fetch
		* @return vertex array object of the model
		*/
		unsigned int GetModel(const std::string& gameModelName);

	private:

		/**
		* Model Struct
		*/
		struct ModelStruct
		{
			/* OpenGL Object that stores all of the state needed to supply vertex data */
			unsigned int vao;

			/* OpenGL Buffer Objects which are used as the source for vertex array data */
			std::vector<unsigned int> vbos;

			/* Model Struct Default Constructor */
			explicit ModelStruct() {}
		};

		/**
		 * Internal Model Map 
		 * Key: Model Name
		 * Value: Model Struct
		 */
		std::map<std::string, ModelStruct> model_map_;
	};
}