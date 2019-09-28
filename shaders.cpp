#include<GL/glew.h>
#include<GL/glut.h>
#include<iostream>
#include<string>
#include<math.h>

//writing shaders for the prg

std::string vertexShader = "#version 130\n"
                            "in vec3 pos;"
                            "void main() {"
                            "gl_Position = vec4(pos, 1);"
                            "}";

std::string fragmentShader = "#version 130\n"
                            "uniform vec4 ourColor;\n"
                            "void main () {"
                            "gl_FragColor = ourColor;\n"
                            "}";

// COMPILE AND CREATE SHADER & returns its ID
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
        std::cout << "Cannot Compile Shader: " << cMessage; 
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

// Load data in VBO and return the vbo's id 
GLuint loadDataInBuffers() 
{ 
    GLfloat vertices[] = { // vertex coordinates 
                           -0.7, -0.7, 0, 
                           0.7, -0.7, 0, 
                           0, 0.7, 0 
    }; 
  
    GLuint vboId; 
  
    // allocate buffer sapce and pass data to it 
    glGenBuffers(1, &vboId); 
    glBindBuffer(GL_ARRAY_BUFFER, vboId); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
  
    // unbind the active buffer 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
  
    return vboId; 
} 
GLuint prgId;

// INITIALIZING
void init() 
{ 
    // clear the framebuffer each frame with black color 
    glClearColor(0, 0, 0, 0); 
  
    GLuint vboId = loadDataInBuffers(); 
  
    GLuint vShaderId = compileShaders(vertexShader, GL_VERTEX_SHADER); 
    GLuint fShaderId = compileShaders(fragmentShader, GL_FRAGMENT_SHADER); 
  
    prgId = linkProgram(vShaderId, fShaderId); 
  
    // Get the 'pos' variable location inside this program 
    GLuint posAttributePosition = glGetAttribLocation(prgId, "pos"); 
  
    GLuint vaoId; 
    glGenVertexArrays(1, &vaoId); // Generate VAO 
  
    // Bind it so that rest of vao operations affect this vao 
    glBindVertexArray(vaoId); 
  
    // buffer from which 'pos' will recive its data and the format of that data 
    glBindBuffer(GL_ARRAY_BUFFER, vboId); 
    glVertexAttribPointer(posAttributePosition, 3, GL_FLOAT, false, 0, 0); 
  
    // Enable this attribute array linked to 'pos' 
    glEnableVertexAttribArray(posAttributePosition); 
  
    // Use this program for rendering. 
    glUseProgram(prgId); 
} 

void display() 
{ 
    // clear the color buffer before each drawing 
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    //to create variable color effect
    static float time = 0;
    time += 0.015;
    float red = sin(time) / 2.0f +0.5f;
    int color = glGetUniformLocation(prgId, "ourColor");
    glUniform4f(color, red, 0.65f, 0.47f, 1.0f);

    // draw triangles starting from index 0 and using 3 indices 
    glDrawArrays(GL_TRIANGLES, 0, 3); 
  
    // swap the buffers and hence show the buffers  
    // content to the screen 
    glutSwapBuffers(); 
    
    //to implement variable color display
    display();
} 
  
// main function 
// sets up window to which we'll draw 
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