#pragma once
#include <map>
#include "shader_manager.h"
#include "../Rendering/object.h"
#include "../Rendering/Models/triangle.h"
#include "../Rendering/Models/quad.h"

using namespace Rendering;
namespace Managers
{
	class ModelManager
	{
	public:
		ModelManager();
		~ModelManager();

		void Draw();
		void Update();
		void DeleteModel(const std::string& gameModelName);
		const ObjectInterface& GetModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, ObjectInterface*> model_map_;
	};
}