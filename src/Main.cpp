/*********************************************************************
 How to compile this on different platforms:

 g++ Main.cpp DrawUtils.cpp CharacterDef.cpp npcHandler.cpp BackgroundDef.cpp `pkg-config --cflags --libs sdl2 gl glew` -o CFramework


 g++ -g Main.cpp DrawUtils.cpp CharacterDef.cpp npcHandler.cpp BackgroundDef.cpp `pkg-config --cflags --libs sdl2 gl glew` -o CFramework
gdb ./	
*/
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include "npcHandler.h"
//#include "CharacterDef.h"
#include "BackgroundDef.h"
#include "AABB.h"
//#include "Projectile.h"
//#include"DrawUtils.h"
#include<vector>


/* Set this to true to force the game to exit */
char shouldExit = 0;

/* The previous frame's keyboard state */
unsigned char kbPrevState[SDL_NUM_SCANCODES] = {0};

/* The current frame's keyboard state */
const unsigned char* kbState = NULL;


/* size of the sprite */
int spriteSize[2];


int main(void)
{
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL. ErrorCode=%s\n", SDL_GetError());
        return 1;
    }

    /* Create the window, OpenGL context */
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    int wWidth = 640;
    int wHeight = 480;
    SDL_Window* window = SDL_CreateWindow(
            "TestSDL",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            wWidth, wHeight,
            SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Could not create window. ErrorCode=%s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_GL_CreateContext(window);

    /* Make sure we have a recent version of OpenGL */
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        fprintf(stderr, "Could not initialize glew. ErrorCode=%s\n", glewGetErrorString(glewError));
        SDL_Quit();
        return 1;
    }
    if (GLEW_VERSION_3_0) {
        fprintf(stderr, "OpenGL 3.0 or greater supported: Version=%s\n",
                 glGetString(GL_VERSION));
    } else {
        fprintf(stderr, "OpenGL max supported version is too low.\n");
        SDL_Quit();
        return 1;
    }

    /* Setup OpenGL state */
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 640, 480, 0, 0, 100);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Load the texture */
    //set Megaman
    /*
    CharacterDef megaman("Mega-Man-Right.tga", "Mega-Man-Left.tga", "Mega-Man-Left.tga", "Mega-Man-Right.tga", 1);
    std::vector<CharacterDef> characterStack;
    characterStack.push_back(megaman);
    characterStack.reserve(15);
    
    for(int i = 0; i < 10; i++){
      //  characterStack.push_back(CharacterDef("DragonUp.tga", "DragonDown.tga", "DragonLeft.tga", "DragonRight.tga", 4));
    }

    
    //set location of sprite
    for(int i = 1; i < characterStack.size(); i++){
       // characterStack[i].setLocation(i*100,i*100);
    }
    characterStack[0].setLocation(40,40);
    */
    kbState = SDL_GetKeyboardState(NULL);
    

    /* The game loop */
    float sizeMultiplier = 1.0;
    BackgroundDef bg(sizeMultiplier);



    // Physics runs at 100fps, or 10ms / physics frame
    unsigned int physicsDeltaMs = 10;
    unsigned int lastPhysicsFrameMs;
    unsigned int curFrameMs;
    unsigned int deltaTime;
    int cameraSpd = 4;
    int refireRate = 150;
    int lastBulletFired = lastPhysicsFrameMs;
    int lastExplosionFired = lastPhysicsFrameMs;
    int winBannerW, winBannerH, loseBannerW, loseBannerH;
    GLuint winBanner = glTexImageTGAFile("FinishBanner.tga", &winBannerW,&winBannerH);
    GLuint loseBanner = glTexImageTGAFile("DeathBanner.tga", &loseBannerW, &loseBannerH);
    srand(time(NULL));
    npcHandler npcs = npcHandler(&bg);
    while (!shouldExit) {
        assert(glGetError() == GL_NO_ERROR);
        memcpy(kbPrevState, kbState, sizeof(kbPrevState));
        curFrameMs = SDL_GetTicks();
        
        deltaTime = curFrameMs - lastPhysicsFrameMs;

        //draw background
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        /* Handle OS message pump */
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    shouldExit = 1;
            }
        }

        // 1. Physics movement
        if (kbState[SDL_SCANCODE_LEFT]) {
            npcs.movePlayer(-1, 0, deltaTime);
        }
        if (kbState[SDL_SCANCODE_RIGHT]) {
            npcs.movePlayer(1, 0, deltaTime);
        }
        if (kbState[SDL_SCANCODE_UP]) {
            npcs.movePlayer(0, -1, deltaTime);
        }
        if (kbState[SDL_SCANCODE_DOWN]) {
            npcs.movePlayer(0, 1, deltaTime);
        }
        if (kbState[SDL_SCANCODE_G]) {
            //reset;
            npcs = npcHandler(&bg);

        }
        // 2. Physics collision detection

        // 3. Physics collision resolution
        
        /* Game logic */
        
        if(kbState[SDL_SCANCODE_W]){
        	bg.scrollUp(cameraSpd);
        }
        if(kbState[SDL_SCANCODE_A]){
        	bg.scrollLeft(cameraSpd);
        }
        if(kbState[SDL_SCANCODE_S]){
        	bg.scrollDown(cameraSpd);
        }
        if(kbState[SDL_SCANCODE_D]){
        	bg.scrollRight(cameraSpd);
        }
        if(kbState[SDL_SCANCODE_SPACE]){
            if(!kbPrevState[SDL_SCANCODE_SPACE]){
        	   npcs.test();
            }
        }


		
        bg.drawBackground();
        /* 
        for(int i = 0; i < characterStack.size(); i++){
            if(bg.checkBox(characterStack[i].getBox())) {
            	glDrawSprite(characterStack[i].getSprite(), characterStack[i].getX() - bg.getX(), 
                    characterStack[i].getY() - bg.getY(), characterStack[i].getW(), characterStack[i].getH());
            }
        }
        for(int i = 0; i < projectileStack.size(); i++){
            if(bg.checkBox(projectileStack[i].getBox())) {
                glDrawSprite(projectileStack[i].picture, projectileStack[i].getX() - bg.getX(), 
                    projectileStack[i].getY() - bg.getY(), projectileStack[i].getW(), projectileStack[i].getH());
            } 
        }

        for(int i = 0; i < projectileStack.size(); i++){
            if(!projectileStack[i].visible){
                projectileStack.erase(projectileStack.begin() + i);
            }
        }
        */

        npcs.update(deltaTime);
        npcs.draw();
        if(npcs.lose){
            glDrawSprite(loseBanner, 150, 200, loseBannerW, loseBannerH);
            printf("die\n");
        }else if(npcs.win){
            glDrawSprite(winBanner, 150, 200, winBannerW, winBannerH);
            printf("win\n");
        }

        if (kbState[SDL_SCANCODE_ESCAPE]) {
            shouldExit = 1;
        }
        /* Present to the player */
        SDL_GL_SwapWindow(window);
        lastPhysicsFrameMs = curFrameMs;
    }

    SDL_Quit();

    return 0;
}


