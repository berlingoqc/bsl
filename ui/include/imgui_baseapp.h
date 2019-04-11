//
// Created by wq on 19-04-10.
//

#ifndef BSL_IMGUI_BASEAPP_H
#define BSL_IMGUI_BASEAPP_H

#include "header.h"

#include <glm/vec4.hpp>
#include <string>


namespace bsl::ui {
	class BaseApp {



	public:
		BaseApp();
		void run();
		std::string			applicationName;
		glm::vec4 			backgroundColor;
		int 				width, height;

	private:
		GLFWwindow*			window;

		void initializeContext();

		void preLoop();
		void afterLoop();

	protected:
		void shutdown();
		virtual void mainLoop() {}
	};

}

#endif //BSL_IMGUI_BASEAPP_H
