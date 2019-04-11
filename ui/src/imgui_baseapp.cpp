//
// Created by wq on 19-04-10.
//

#include "imgui.h"
#include "imgui_baseapp.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace bsl::ui {
    BaseApp::BaseApp() : width(1280), height(720) {}

    void BaseApp::run() {
        try {
            initializeContext();
            while(!glfwWindowShouldClose(window)) {
                preLoop();
                mainLoop();
                afterLoop();
            }
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        END_PROGRAM(EXIT_SUCCESS);
    }


    void BaseApp::initializeContext() {
        //glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
        {
            std::cerr << "Erreur initialisation glfw" << std::endl;
            return;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        GLFWwindow*	window = glfwCreateWindow(width, height, applicationName.c_str(), nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            std::cerr << "Erreur creation de la fenetre glfw" << std::endl;
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // vsync

#ifndef EMSCRIPTEN
        int v = glewInit();
#endif

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(SHADER_VERSION);

        // Setup Style
        ImGui::StyleColorsDark();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifndef EMSCRIPTEN
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
#endif
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);

        this->window = window;
    }

    void BaseApp::preLoop() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void BaseApp::afterLoop() {
        // Rendering de ImGui par dessus mon stock
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwMakeContextCurrent(window);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    void BaseApp::shutdown() {
        glfwTerminate();
    }
}
