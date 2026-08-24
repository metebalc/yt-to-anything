#include <iostream>
#include <string>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "converter.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwSetErrorCallback(error_callback);
    
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "YT to Anything", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    
    }
    
	glfwSetKeyCallback(window, key_callback);
    
    glfwMakeContextCurrent(window);
    
    int version = gladLoadGL(glfwGetProcAddress);

	if (version == 0)
	{
		std::cerr << "Failed to initialize GLAD\n";

		glfwDestroyWindow(window);
		glfwTerminate();

		return EXIT_FAILURE;
	}

	std::cout << "OpenGL version: "
			  << GLAD_VERSION_MAJOR(version)
			  << "."
			  << GLAD_VERSION_MINOR(version)
			  << '\n';


    Converter converter;

    std::string websiteUrl;

    std::cout << "Enter URL: ";
    std::getline(std::cin, websiteUrl);

    converter.setWebsiteUrl(websiteUrl);

    int result = converter.convertToOgg();

    if (result != 0)
    {
        std::cerr << "yt-dlp failed with exit code "<< result << '\n';

        glfwDestroyWindow(window);
        glfwTerminate();

        return EXIT_FAILURE;
    }

    std::cout << "Download complete.\n";

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.12f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
