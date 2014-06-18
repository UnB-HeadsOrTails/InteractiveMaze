#include "drawable_manager.h"

DrawableManager::DrawableManager()
{

}

void
DrawableManager::addDrawable(Drawable *drawable)
{
	this->drawableList.push_back(drawable);
}

void
DrawableManager::removeDrawable(Drawable *drawable)
{
	this->drawableList.remove(drawable);
}

void
DrawableManager::run()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*) 0);
	glVertexAttribPointer(1, 4, GL_INT, GL_TRUE, sizeof(Vertex), (const GLvoid*) 3);

	list<Drawable *>::iterator it;
	it = this->drawableList.begin();

	for(; it != this->drawableList.end(); it++)
	{
		(*it)->draw();
	}

	glDisableVertexAttribArray(0);
  	glDisableVertexAttribArray(1);
}


GLuint
DrawableManager::initShader()
{
  GLuint program = glCreateProgram();
  cout << "DENTRO DO INIT" << endl;
    
  for ( int i = 0; i < 2; ++i ) 
  {
    Shader &s = this->shaders[i];
    s.source = readShaderSource(s.filename);

    if (shaders[i].source == NULL) 
    {
	    printf("\nFailed to read %s ", s.filename);
	    exit(EXIT_FAILURE);
    }

    GLuint shader = glCreateShader(s.type);
	  glShaderSource(shader, 1, (const GLchar**) &s.source, NULL);
	  glCompileShader(shader);

    GLint  compiled;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	  if (!compiled) 
    {
      printf("\n \n failed to compile: %s", s.filename);
		  GLint  logSize;
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog(shader, logSize, NULL, logMsg);
		
		  printf("\n \n logSize %i failed to compile: %s",logSize, logMsg);
		  scanf("%i",&i);
		  exit(EXIT_FAILURE);
	  }

	  glAttachShader(program, shader);
  }

  glLinkProgram(program);

  GLint  linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);

  if (!linked) 
  {
	  GLint  logSize;
	  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
	  char* logMsg = new char[logSize];
	  glGetProgramInfoLog(program, logSize, NULL, logMsg);

	  exit( EXIT_FAILURE );
  }

  glUseProgram(program);

  return program;
}

void
DrawableManager::criarVertexArray()
{
  glGenVertexArrays(1, &this->vertexArrayID); 
  glBindVertexArray(vertexArrayID);
}