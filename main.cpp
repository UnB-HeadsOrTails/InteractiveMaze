#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "point3d.h"
#include "screen.h"
#include "camera.h"
#include "mesh.h"

using namespace std;

const float VELOCITY_MOVE_OBJECT = 0.05;
const float VELOCITY_ANGLE_OBJECT = 5.0;

const float VELOCITY_MOVE_CAMERA = 0.05;
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

int main()
{
	bool finish;
	Screen screen;

	cout << "1 - Use as SETAS para MOVER o COELHO;" << endl;
	cout << "2 - Use PAGEUP para AMPLIAR e PAGEDOWN para REDIZIR o TAMANHO do COELHO;" << endl;
	cout << "3 - Pressione L para MOSTRAR o COELHO como LINHAS;" << endl;
	cout << "3 - Pressione T para MOSTRAR o COELHO como PLANO;" << endl;

	char lineType;
	string fileName;
	while(cin >> lineType)
	{
		if(lineType == 'M')
		{
			cin >> fileName;
			Mesh mesh;
			mesh.loadFile(fileName);
			mesh.setPosition(0.0, 0.0, 0.0);
			mesh.resizeToScreen();

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
			vectorMesh[meshIndex].showDimensions();
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