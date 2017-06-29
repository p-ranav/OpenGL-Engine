/*
* Author: Pranav Srinivas Kumar
*/
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
			auto console = spdlog::stdout_color_mt("console");
			name = "Engine";
			width = 800; height = 600;
			position_x = 300;
			position_y = 300;
			is_reshapable = true;
		}

		/**
		 * WindowInfo Overloaded Constructor
		 * @param name Name of the Window
		 * @param start_position_x X coordinates value of the initial position of the window
		 * @param start_position_y Y coordinates value of the initial position of the window
		 * @param width Width of the Window
		 * @param height Height of the Window
		 * @param is_reshapable Is this window reshapable?
		 */
		WindowInfo(std::string name, int start_position_x, int start_position_y, int width, int height, bool is_reshapable)
		{
			size_t queue_size = 4096;
			spdlog::set_async_mode(queue_size);
			auto console = spdlog::stdout_color_mt("console");
			name = name;
			position_x = start_position_x;
			position_y = start_position_y;
			width = width;
			height = height;
			is_reshapable = is_reshapable;
		}

		/**
		 * WindowInfo Copy Constructor
		 * @param window_info WindowInfo struct to copy
		 */
		WindowInfo(const WindowInfo& window_info)
		{
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
		void operator=(const WindowInfo& window_info)
		{
			name = window_info.name;
			position_x = window_info.position_x;
			position_y = window_info.position_y;
			width = window_info.width;
			height = window_info.height;
			is_reshapable = window_info.is_reshapable;
		}

	};
}