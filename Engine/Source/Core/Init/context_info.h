#pragma once

namespace Core {

	/**
	 * OpenGL Context Information
	 */
	struct ContextInfo
	{
		/* Major and Minor version of the context */
		int major_version, minor_version;

		/* Core OpenGL? */
		bool core;

		/* ContextInfo Default Constructor */
		ContextInfo() {
			major_version = 3;
			minor_version = 3;
			core = true;
		}

		/**
		 * ContextInfo Overloaded Constructor
		 * @param major_version Major Version Number
		 * @param minor_version Minor Version Number
		 * @param core Core or Not?
		 */
		ContextInfo(int major_version_number, int minor_version_number, bool is_core) {
			major_version = major_version_number;
			minor_version = minor_version_number;
			core = is_core;
		}

		/**
		 * Overloaded Assignemnt Operator
		 * @param info Another ContextInfo struct
		 */
		void operator= (const ContextInfo &info) {
			major_version = info.major_version;
			minor_version = info.minor_version;
			core = info.core;
		}
	};
}