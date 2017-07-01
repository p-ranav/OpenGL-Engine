#pragma once

// External Headers
#include "glew.h"
#include "freeglut.h"

namespace Core {

	/**
	 * FrameBufferInfo Struct - OpenGL Display Mode
	 */
	struct FrameBufferInfo {

		/* OpenGL Display Mode Flags */
		unsigned int flags;

		/* Enable or Disable Multi-Sample Anti Aliasing */
		bool msaa;

		/* FrameBufferInfo Default Constructor */
		FrameBufferInfo() {
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaa = false;
		}

		/** 
		 * FrameBufferInfo Overloaded Constructor 
		 * @param color Flag to add alpha component to color
		 * @param depth Flag to enable depth buffer (aka Z buffer)
		 * @param stencil Flag to enable stencil buffer
		 * @param msaa Flag to support multi-sampling (enable it later with glEnable(GL_MULTISAMPLE))
		 */
		FrameBufferInfo(bool color, bool depth, bool stencil, bool msaa) {
			flags = GLUT_DOUBLE; //this is a must
			if (color)
				flags |= GLUT_RGBA | GLUT_ALPHA;
			if (depth)
				flags |= GLUT_DEPTH;
			if (stencil)
				flags |= GLUT_STENCIL;
			if (msaa)
				flags |= GLUT_MULTISAMPLE;
			this->msaa = msaa;
		}

		/**
		 * Overloaded assignment operator
		 * @param info Another FrameBufferInfo struct
		 */
		void operator=(const FrameBufferInfo& info) {
			flags = info.flags;
			msaa = info.msaa;
		}
	};
}