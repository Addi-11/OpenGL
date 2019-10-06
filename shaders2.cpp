#include<GL/glew.h>
#include<GL/glut.h>
#include<iostream>
#include<string>
#include<math.h>

//writing shaders

std::string vertexShader = "#version 130\n"
                            "layout (location = 0) in vec3 aPos;\n"
                            "layout (location = 1) in vec3 aColor;\n"
                            "out vec3 ourColor;\n"
                            "void main() { \n"
                            "gl_positon = vec4(aPos, 1.0);\n"
                            "ourColor = aColor;"
                            "}";
std::string fragmentShader = "#version 130\n"
                            "out vec4 FragColor;\n"
                            "in vec3 ourColor;\n"
                            "void main() {\n"
                            "FragColor = vec4(ourColor, 1.0f);\n"
                            "}";

//compiling shaders
GLuint compileShaders(std::string shader, GLenum type){

    const char* shaderCode = shader.c_str();
    GLuint shaderId = glCreateShader(type);

    //error handling
    if(shaderId == 0) {
        std::cout << "\nError creating shaders";
        return 0;
    }

    //attaching code to the object
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    GLint compileStatus;

    //checking compilation status -- error handling
    glGetShaderiv(shaderId,GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) { 
        int length; 
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length); 
        char* cMessage = new char[length]; 
  
        // Get additional information 
        glGetShaderInfoLog(shaderId, length, &length, cMessage); 
        std::cout << "Cannot Compile Shader: " << type<< cMessage; 
        delete[] cMessage; 
        glDeleteShader(shaderId); 
        return 0; 
    } 

    return shaderId;
}

// Creates PROGRAM CONTAINING VERTEX & FRAGMENT SHADER & LINKING them

GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId) 
{ 
    GLuint programId = glCreateProgram(); // create a program 
    
    //error handling
    if (programId == 0) { 
        std::cout << "Error Creating Shader Program"; 
        return 0; 
    } 
  
    // Attach both the shaders to program
    glAttachShader(programId, vertexShaderId); 
    glAttachShader(programId, fragmentShaderId); 
  
    // Create executable of this program 
    glLinkProgram(programId); 
  
    
    // Get the link status for this program 
    GLint linkStatus; 
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus); 
  
    if (!linkStatus) { // If the linking failed 
        std::cout << "Error Linking program"; 
        glDetachShader(programId, vertexShaderId); 
        glDetachShader(programId, fragmentShaderId); 
        glDeleteProgram(programId); 
  
        return 0; 
    } 
  
    return programId; 
} 

GLuint loadDataInBuffers() 
{ 
    GLfloat vertices[] = {  
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
    }; 
  
    GLuint vboId ; 
  
    // allocate buffer sapce and pass data to it 
    glGenBuffers(1, &vboId); 
    glBindBuffer(GL_ARRAY_BUFFER, vboId); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // unbind the active buffer 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
  
    return vboId; 
} 
void init() 
{ 
    // clear the framebuffer each frame with black color 
    glClearColor(0, 0, 0, 0); 
  
    GLuint vboId = loadDataInBuffers(); 
  
    GLuint vShaderId = compileShaders(vertexShader, GL_VERTEX_SHADER); 
    GLuint fShaderId = compileShaders(fragmentShader, GL_FRAGMENT_SHADER); 
  
    GLuint prgId = linkProgram(vShaderId, fShaderId); 
  
    GLuint vaoId; 
    glGenVertexArrays(1, &vaoId); // Generate VAO 
  
    // Bind it so that rest of vao operations affect this vao 
    glBindVertexArray(vaoId); 
  
    // buffer from which 'pos' will recive its data and the format of that data 
    glBindBuffer(GL_ARRAY_BUFFER, vboId); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); 
  
    // Use this program for rendering. 
    glUseProgram(prgId); 
}

void display() 
{ 
    // clear the color buffer before each drawing 
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);


    // draw triangles starting from index 0 and using 3 indices 
    glDrawArrays(GL_TRIANGLES, 0, 3); 
  
    // swap the buffers and hence show the buffers  
    // content to the screen 
    glutSwapBuffers(); 
    
} 

 
int main(int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
    glutInitWindowSize(500, 500); 
    glutInitWindowPosition(100, 50); 
    glutCreateWindow("Triangle Using OpenGL"); 
    glewInit(); 
    init(); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
}  