#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "point3d.h"
#include "screen.h"
#include "camera.h"
#include "mesh.h"

using namespace std;

const float VELOCITY_MOVE_OBJECT = 0.1;
const float VELOCITY_ANGLE_OBJECT = 5.0;

const float VELOCITY_MOVE_CAMERA = 0.1;
const float VELOCITY_ROTATE_CAMERA = 0.005;
const float VELOCITY_ANGLE_CAMERA = 0.05;

int meshIndex = 0;
float velocityX = 0, velocityY = 0, velocityZ = 0;
float velocityAngleX = 0, velocityAngleY = 0, velocityAngleZ = 0;

float velocityCameraX = 0, velocityCameraY = 0, velocityCameraZ = 0;
float velocityCameraAngleX = 0, velocityCameraAngleY = 0, velocityCameraAngleZ = 0;

vector<Mesh> vectorMesh;

SDL_Event sdlEvent;

Camera camera;

void moveCamera();
void moveObjects();
void (*keyboardFunction)();

void printInstructions();

int main()
{
	bool finish;
	Screen screen;

	printInstructions();

	char lineType;
	string fileName;
	while(cin >> lineType)
	{
		if(lineType == 'M')
		{
			float x, y, z;

			cin >> fileName;
			cin >> x >> y >> z;
			Mesh mesh;
			mesh.loadFile(fileName);
			mesh.resizeToScreen();
			mesh.setPosition(x, y, z);
			// mesh.translate();

			vectorMesh.push_back(mesh);
		}
	}

	for(int i = 0; i < (int)vectorMesh.size(); i++)
	{
		screen.addDrawable(&(vectorMesh[i]));
	}

	glEnable(GL_DEPTH_TEST);

	finish = false;
	keyboardFunction = moveCamera;

	// gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
  	// glEnable(GL_MULTISAMPLE);

	while(!finish)
	{
		while(SDL_PollEvent(&sdlEvent))
		{
			if(sdlEvent.type == SDL_QUIT)
			{
				finish = true;
				break;
			}

			if(sdlEvent.key.keysym.sym == SDLK_1)
			{
				if(sdlEvent.key.state == SDL_PRESSED)
				  keyboardFunction = moveCamera;
			}

			if(sdlEvent.key.keysym.sym == SDLK_2)
			{
				if(sdlEvent.key.state == SDL_PRESSED)
				  keyboardFunction = moveObjects;
			}

			keyboardFunction();
		}

		vectorMesh[meshIndex].incPosition(velocityX, velocityY, velocityZ);
		vectorMesh[meshIndex].rotateX(velocityAngleX);
		vectorMesh[meshIndex].rotateY(velocityAngleY);
		vectorMesh[meshIndex].rotateZ(velocityAngleZ);

		camera.moveFrontAndBack(velocityCameraY);
		camera.rotateRightAndLeft(velocityCameraX);

		// camera.incPosition(velocityCameraX, velocityCameraY, velocityCameraZ);
		// camera.rotate(velocityCameraAngleX, velocityCameraAngleY, velocityCameraAngleZ);

		// camera.update();

		// gluLookAt(pointCameraEye.x, pointCameraEye.y, pointCameraEye.z,
		//           pointCameraReference.x, pointCameraReference.y, pointCameraReference.z,
		//           pointCameraUp.x, pointCameraUp.y, pointCameraUp.z);
		// glTranslatef(velocityCameraX, velocityCameraY, velocityCameraZ);
		// glRotatef(velocityCameraAngleX, 1.0f, 0.0f, 0.0f);
		// glRotatef(velocityCameraAngleY, 0.0f, 1.0f, 0.0f);
		// glRotatef(velocityCameraAngleZ, 0.0f, 0.0f, 1.0f);

		screen.render();
		SDL_Delay(36);
	}


	return 0;
}

void moveCamera()
{
	if(sdlEvent.key.keysym.sym == SDLK_UP)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraY = VELOCITY_MOVE_CAMERA;
		else
			velocityCameraY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_DOWN)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraY = -VELOCITY_MOVE_CAMERA;
		else
			velocityCameraY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_LEFT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraX = -VELOCITY_ROTATE_CAMERA;
		else
			velocityCameraX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_RIGHT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraX = VELOCITY_ROTATE_CAMERA;
		else
			velocityCameraX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_m)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraZ = -VELOCITY_MOVE_CAMERA;
		else
			velocityCameraZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_n)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraZ = VELOCITY_MOVE_CAMERA;
		else
			velocityCameraZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_w)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleX = VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_s)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleX = -VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_d)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleY = VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_a)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleY = -VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_e)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleZ = VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_q)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityCameraAngleZ = -VELOCITY_ANGLE_CAMERA;
		else
			velocityCameraAngleZ = 0;
	}

}

void moveObjects()
{
	if(sdlEvent.key.keysym.sym == SDLK_r)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].setDeltaX(4);
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_p)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].showPosition();
			vectorMesh[meshIndex].showDimensions();
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_c)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			meshIndex++;
  			meshIndex = meshIndex % vectorMesh.size();
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_x)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			meshIndex--;
  			meshIndex = meshIndex % vectorMesh.size();
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_r)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].resizeToScreen();
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_PAGEUP)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].resize(1.2);
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_PAGEDOWN)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].resize(0.83);
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_t)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].setType(Mesh::TRIANGLES);
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_l)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
		{
			vectorMesh[meshIndex].setType(Mesh::LINES);
		}
	}

	if(sdlEvent.key.keysym.sym == SDLK_UP)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = VELOCITY_MOVE_OBJECT;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_DOWN)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = -VELOCITY_MOVE_OBJECT;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_LEFT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = -VELOCITY_MOVE_OBJECT;
		else
			velocityX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_RIGHT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = VELOCITY_MOVE_OBJECT;
		else
			velocityX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_m)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityZ = VELOCITY_MOVE_OBJECT;
		else
			velocityZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_n)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityZ = -VELOCITY_MOVE_OBJECT;
		else
			velocityZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_w)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleX = -VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_s)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleX = VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_d)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleY = -VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_a)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleY = VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_e)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleZ = VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleZ = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_q)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityAngleZ = -VELOCITY_ANGLE_OBJECT;
		else
			velocityAngleZ = 0;
	}
}

void printInstructions()
{
	cout << endl;
	cout << "+INSTRUCOES+" << endl;
	cout << endl;

	cout << "+---------------GERAL---------------+" << endl;
	cout << "| 1 - Movimentacao da CAMERA" << endl;
	cout << "| 2 - Movimentacao dos OBJETOS" << endl;
	cout << "+-----------------------------------+" << endl;
	cout << endl;

	cout << "+--------------CAMERA--------------+" << endl;
	cout << "+-----Movimentacao:" << endl;
	cout << "| UP - Andar para frente" << endl;
	cout << "| DOWN - Andar para tras" << endl;
	cout << "| RIGHT - Girar para direita" << endl;
	cout << "| LEFT - Girar para esquerda" << endl;
	cout << "+----------------------------------+" << endl;
	cout << endl;

	cout << "+--------------OBJETOS--------------+" << endl;
	cout << "+-----Movimentacao:" << endl;
	cout << "| UP - Mover no eixo Y +" << endl;
	cout << "| DOWN - Mover no eixo Y -" << endl;
	cout << "| RIGHT - Mover no eixo X +" << endl;
	cout << "| LEFT - Mover no eixo Y -" << endl;
	cout << "| M - Mover no eixo Z +" << endl;
	cout << "| N - Mover no eixo Z -" << endl;
	cout << "+-----:" << endl;

	cout << "+-----Rotacao:" << endl;
	cout << "| W - Rotacionao no eixo X +" << endl;
	cout << "| S - Rotacionao no eixo X -" << endl;
	cout << "| D - Rotacionao no eixo Y +" << endl;
	cout << "| A - Rotacionao no eixo Y -" << endl;
	cout << "| E - Rotacionao no eixo Z +" << endl;
	cout << "| Q - Rotacionao no eixo Z -" << endl;
	cout << "+-----:" << endl;

	cout << "+-----Selecionar Objeto:" << endl;
	cout << "| C - Seleciona o proximo objeto" << endl;
	cout << "| X - Seleciona o objeto anterior" << endl;
	cout << "+-----:" << endl;

	cout << "+-----Renderizacao:" << endl;
	cout << "| L - Renderizar objeto por linha" << endl;
	cout << "| T - Renderizar objeto por plano" << endl;
	cout << "+-----:" << endl;
	cout << endl;
	cout << "+-----------------------------------+" << endl;
	cout << endl;	
}