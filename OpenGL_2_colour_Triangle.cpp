#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

// Ввод с клавиатуры
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) 

// Размеры окна
const GLuint WIDTH = 800, Height = 600;

// Шейдеры----------------------------------------------------------------
    
    // vertex
    const GLchar* vertexShaderSource = "#version 330 core\n" // версия совпадает с версией OpenGL
        "layout (location = 0) in vec3 position;" // входные вершинные атрибуты
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    
    // fragment 1st colour
    const GLchar* fragmentShader1Source = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    // fragment 2nd colour
    const GLchar* fragmentShader1Source = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";
//----------------------------------------------------------------

int main() 
{
    // инициализируем GLFW:
    glfwInit(); // Инициализация GLFW
    // Настройка GLFW
        // Задаем минимальную требуемую версию OpenGL
        glfwWindowHint(GLDW_CONTEXT_VERSION_MAJOR, 3); // мажорная
        glfwWindowHint(GLDW_CONTEXT_VERSION_MINOR, 3); // минорная
        // Установка профайла, для которого создается контекст
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Выключение возможности изменения размера окна
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        
    // создаем объект окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "Треугольник", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Устанавливаем функцию key_callback() в GLFW
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE; // инициализируем GLEW (управляет указателями на функции OpenGL)
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // можно попробовать просто glewInit();
    
    // сообщаем размер отрисованного окна
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height); // устанавливаем значения через glViewport()
    // Первые 2 аргумента функции glViewport — это позиция нижнего левого угла окна.
    //Третий и четвертый — это ширина и высота отрисовываемого окна в px, которые мы получаем напрямую из GLFW
    
    // создаем и компилируем шейдерную программу----------------------------------------------------------------
        
            GLunit vertexShader; // создаем переменную
            vertexShader = glCreateShader(GL_VERTEX_SHADER); // через glCreateShader (VERTEX_SHADER - вершинный шейдер)
            
            GLunit fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
            GLunit fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
            GLunit shaderProgramOrange = glCreateProgram();
            GLunit shaderProgramRed = glCreateProgram();
            
            // Привязываем исходный код шейдера к объекту шейдера и компилируем
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // аргументы: шейдер, кол-во строк, исходный код шейдера
            glCompileShader(vertexShader);
            glShaderSource(fragmentShaderOrangeShader, 1, &vertexShader1Source, NULL);
            glCompileShader(fragmentShaderOrange);
            glShaderSource(fragmentShaderRed, 1, &vertexShader2Source, NULL);
            glCompileShader(fragmentShaderRed);
            
            // ищем ошибки
            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertexShader, 515, NULL, infolog);
                std::cout << "ERROR::SHADER;;VERTEX;;COMPILATION_FAILED\n" << infolog << std::endl; // собственно, сообщаем об этом
            }
        
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
             if (!success) {
                glGetShaderInfoLog(fragmentShader, 515, NULL, infolog);
                std::cout << "ERROR::SHADER;;FRAGMENT;;COMPILATION_FAILED\n" << infolog << std::endl;
            }
            
    //----------------------------------------------------------------
    
    // шейдерная программа
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);
    
    // ищем ошибки
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER;;PROGRAM;;COMPILATION_FAILED\n" << infolog << std::endl;
    }
    
    // Удаляем созданные шейдеры после связывания
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    

    GLfloat orangeTriangle[] = {
        //первый
         0.0f,  0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
         0.5f,  0.0f,  0.0f
    };
    GLfloat redTriangle[] = {
          0.0f, -0.5f, 0.0f,  
         -0.5f, -0.5f, 0.0f,  
         -0.5f,  0.0f, 0.0f   
    };
    
    // Создание объекта вершинного буфера VBO и вершинного массива VAO
    GLunit VBOs[2], VAOs[2];
    glGenBuffers(2, &VBOs);
    glGenVertexArrays(2, &VAOs);
    
    // Теперь мы должны настроить(привязать) требуемые VBO и указатели на атрибуты,------------------------
    //а в конце отвязать VAO для последующего использования:
        
        // first-----------------------------
        //-привязываем VAO
        glBindVertexArray(VAOs[0]);
        //-копируем массив вершин в буфер для OpenGL
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(orangeTriangle), orangeTriangle, GL_STATIC_DRAW);
        //-устанавливаем указатели на вершинные атрибуты
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        //-передаем вершинному атрибуту позицию аргумента
        glEnableVertexAttribArray(0);
        // чистим массив вершин
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //-отвязываем VAO
        glBindVertexArray(0);
        
        //second-------------------------------
        glBindVertexArray(VAOs[1]);
        //-копируем массив вершин в буфер для OpenGL
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(redTriangle), redTriangle, GL_STATIC_DRAW);
        //-устанавливаем указатели на вершинные атрибуты
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        //-передаем вершинному атрибуту позицию аргумента
        glEnableVertexAttribArray(0);
        // чистим массив вершин
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //-отвязываем VAO
        glBindVertexArray(0);
    
    //-----------------------------------------------------------------------------------
    
    // Игровой цикл:
    
    while(!glfwWindowShouldClose(window)) {
        
        // проверяем, были ли вызваны какие либо события и вызываем установленные функции
        glfwPollEvents();
         // очищаем цветовой буффер
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // установили требуемый цвет
        glClear(GL_COLOR_BUFFER_BIT); // использовали установленный цвет
        
        glUseProgram(shaderProgramOrange);
        //первый
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //второй
        glUseProgram(shaderProgramRed);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window); //заменяет цветовой буфер (большой буфер, содержащий значения цвета для каждого пикселя в GLFW окне),
        //который использовался для отрисовки во время текущей итерации и показывает результат на экране
    }
    
    // освобождаем ресурсы, как только в VAO и VBO отпала необходимость
    glDeleteVertexArrays(2, &VAOs);
    glDeleteBuffers(2, &VBOs);
     // завершаем работу GLFW, очистив все ресурсы, выделенные GLFW.
    glfwTerminate();
    
return 0;
}

// Функция закрытия окна
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) // Функция ввода с клавиатуры
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // Когда нажимается клавиша Esc
        gldwSetWindowShouldClose(window, GL_TRUE); // Закрываем окно

}