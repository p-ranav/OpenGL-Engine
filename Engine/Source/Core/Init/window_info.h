#pragma once

// External Headers
#include "spdlog\spdlog.h"

// System Headers
#include <string>

namespace Core
{
	/**
	 * Window Information
	 */
	struct WindowInfo
	{
		/* Name of the Window */
		std::string name;

		/* Width and Height of the Window */
		int width, height;

		/* Position of the Window */
		int position_x, position_y;

		/* Is this window reshapable? */
		bool is_reshapable;

		/**
		 * WindowInfo Default Constructor
		 */
		WindowInfo()
		{
			size_t queue_size = 4096;
			spdlog::set_async_mode(queue_size);
			auto console = spdlog::get("console");
			if (!console)
				console = spdlog::stdout_color_mt("console");
			name = "Engine";
			width = 800; height = 600;
			position_x = 300;
			position_y = 300;
			is_reshapable = true;
		}

		/**
		 * WindowInfo Overloaded Constructor
		 * @param new_name Name of the Window
		 * @param new_start_position_x X coordinates value of the initial position of the window
		 * @param new_start_position_y Y coordinates value of the initial position of the window
		 * @param new_width Width of the Window
		 * @param new_height Height of the Window
		 * @param new_is_reshapable Is this window reshapable?
		 */
		WindowInfo(std::string new_name, int new_position_x, int new_position_y, int new_width, int new_height, bool new_is_reshapable) {
			size_t queue_size = 4096;
			spdlog::set_async_mode(queue_size);
			auto console = spdlog::get("console");
			if (!console)
				console = spdlog::stdout_color_mt("console");
			name = new_name;
			position_x = new_position_x;
			position_y = new_position_y;
			width = new_width;
			height = new_height;
			is_reshapable = new_is_reshapable;
		}

		/**
		 * WindowInfo Copy Constructor
		 * @param window_info WindowInfo struct to copy
		 */
		WindowInfo(const WindowInfo& window_info) {
			name = window_info.name;
			position_x = window_info.position_x;
			position_y = window_info.position_y;
			width = window_info.width;
			height = window_info.height;
			is_reshapable = window_info.is_reshapable;
		}

		/**
		* WindowInfo Assignment Operator
		* @param window_info WindowInfo struct to assign
		*/
		void operator=(const WindowInfo& window_info) {
			name = window_info.name;
			position_x = window_info.position_x;
			position_y = window_info.position_y;
			width = window_info.width;
			height = window_info.height;
			is_reshapable = window_info.is_reshapable;
		}

	};
}