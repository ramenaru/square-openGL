#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

int windowWidth = 800, windowHeight = 600;

float squareX = 0.0f, squareY = 0.0f;
float squareSize = 0.2f;
float angle = 0.0f;
float rotationSpeed = 0.5f;
float red = 1.0f, green = 1.0f, blue = 1.0f;

double mouseX, mouseY;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &mouseX, &mouseY);
        squareX = (2.0f * mouseX / windowWidth) - 1.0f;
        squareY = 1.0f - (2.0f * mouseY / windowHeight);
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD) {
            squareSize += 0.05f;
        } else if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT) {
            squareSize -= 0.05f;
            if (squareSize < 0.05f) {
                squareSize = 0.05f;
            }
        } else if (key == GLFW_KEY_R) {
            red = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            green = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            blue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        } else if (key == GLFW_KEY_S) {
            rotationSpeed += 0.1f;
        } else if (key == GLFW_KEY_D) {
            rotationSpeed -= 0.1f;
            if (rotationSpeed < 0.1f) {
                rotationSpeed = 0.1f;
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Rotating Square", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(red, green, blue);

        glPushMatrix();

        glTranslatef(squareX, squareY, 0.0f);

        angle += rotationSpeed * 0.01f;
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        glBegin(GL_QUADS);
        glVertex2f(-squareSize, -squareSize);
        glVertex2f(squareSize, -squareSize);
        glVertex2f(squareSize, squareSize);
        glVertex2f(-squareSize, squareSize);
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}