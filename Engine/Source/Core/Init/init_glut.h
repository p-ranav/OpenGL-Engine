#pragma once

// User-defined Headers
#include "context_info.h"
#include "framebuffer_info.h"
#include "window_info.h"
#include "init_glew.h"
#include "listener.h"

// External Headers
#include "spdlog\spdlog.h"

// System Headers
#include <iostream>

namespace Core {
	namespace Init {

		/**
		 * Class to initialize GLUT
		 */
		class InitGLUT {

		public:
			/**
			 * Initialize OpenGL Context, Display Mode, Window Position and Setup Callbacks
			 * @param window Window information
			 * @param context OpenGL Context Information
			 * @param framebuffer_info FrameBuffer Information
			 */
			static void Init(const Core::WindowInfo& window, const Core::ContextInfo& context, const Core::FrameBufferInfo& framebuffer_info);

			/**
			 * Run begins the rendering loop
			 * Called from main()
			 */
			static void Run();

			/**
			 * Close tears down the rendering
			 */
			static void Close();

			/**
			 * Method to enter fullscreen mode
			 */
			void EnterFullscreen();

			/**
			* Method to exit fullscreen mode
			*/
			void ExitFullscreen();

			/**
			 * Use spdlog and print debug information about OpenGL
			 * Prints vendor, renderer and OpenGL version
			 */
			static void PrintOpenGLInfo();

		private:

			/* Idle Callback while rendering */
			static void IdleCallback(void);

			/* Display Callback while rendering */
			static void DisplayCallback(void);

			/** 
			 * Resizing Callback while rendering 
			 * @param width Resized width
			 * @param height Resized height
			 */
			static void ReshapeCallback(int width, int height);

			/* Callback used during teardown */
			static void CloseCallback();

		private:
			/* Listener - Receives Notifications from SceneManager */
			static Core::ListenerInterface* listener_;

			/* Window Information to be used in callbacks */
			static Core::WindowInfo window_info_;

		public:

			/**
			 * Set the Listener Object
			 * @param listenr Listener Interface Object
			 */
			static void SetListener(Core::ListenerInterface*& listener);
		};
	}
}