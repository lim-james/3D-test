// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(750, 220, "SP1 Framework");

const unsigned int numberOfObjects = 25;
Object **objects;
//Object *player;

Matrix *camera;

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
	srand(time(nullptr));

    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 5, L"Consolas");

	initCamera();
	initObject();
	//initPlayer();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_W] = isKeyPressed(0x57);
	g_abKeyPressed[K_A] = isKeyPressed(0x41);
	g_abKeyPressed[K_S] = isKeyPressed(0x53);
	g_abKeyPressed[K_D] = isKeyPressed(0x44);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: 
			renderSplashScreen();
            break;
		case S_GAME:
			renderObjects(numberOfObjects, objects); //renderGame();
			//renderObject(player);
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP])
    {	
		*camera = camera->rotate(1.0 / 180.0 * M_PI, x);
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_LEFT])
    {
		*camera = camera->rotate(1.0 / 180.0 * M_PI, y);
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_DOWN])
    {
		*camera = camera->rotate(-1.0 / 180.0 * M_PI, x);
		//Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_RIGHT])
    {
		*camera = camera->rotate(-1.0 / 180.0 * M_PI, y);
		//Beep(1440, 30);
        g_sChar.m_cLocation.X++;
        bSomethingHappened = true;
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }
	
	if (g_abKeyPressed[K_W])
	{
		*camera = camera->translate(.1, y);
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_A])
	{
		*camera = camera->translate(-.1, x);
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_S])
	{
		*camera = camera->translate(-.1, y);
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_D])
	{
		*camera = camera->translate(.1, x);
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}
	
    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.01; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x00); //0x1F);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

/*

From this section down, I am trying to render 3D objects onto the screen

*/

void renderObject(Object *o)
{
	for (int i = 0; i < o->verticesCount / 3; ++i) 
	{
		for (int v = 0; v < 3; ++v) {
			Vector *vec =  (Vector*) new Matrix(*camera * o->vertices[i * 3 + v]);
			vec->makePerspective();
			double x = vec->x();
			double y = vec->y();
			renderPoint(x, y, o->color);
			delete vec;
		}
	
		Vector *p1 = (Vector*) new Matrix(*camera * o->vertices[i * 3]);
		Vector *p2 = (Vector*) new Matrix(*camera * o->vertices[i * 3 + 1]);
		Vector *p3 = (Vector*) new Matrix(*camera * o->vertices[i * 3 + 2]);

		p1->makePerspective();
		p2->makePerspective();
		p3->makePerspective();

		renderLine(p1, p2, o->color);
		renderLine(p2, p3, o->color);
		renderLine(p3, p1, o->color);
		delete p1, p2, p3;
	}
	
}

void renderObjects(const unsigned int count, Object **o)
{
	for (int x = 0; x < count; ++x) {
		renderObject(o[x]);
	}
}

void renderLine(Vector* v1, Vector* v2, WORD color)
{
	double d = v1->distance(v2);
	double xDiff = v2->x() - v1->x();
	double yDiff = v2->y() - v1->y();
	double m = yDiff / xDiff;
	double c = m*-v1->x() + v1->y();
	for (double i = 0; i < d; ++i) {
		double x, y;
		if ((int)xDiff == 0) {
			y = i / d * yDiff + v1->y();
			x = v1->x();
		} else {
			x = xDiff * i / d + v1->x();
			y = m * x + c;
		}
		renderPoint(x, y, color);
	}
}

void renderPoint(double x, double y, WORD color) 
{
	COORD c;
	c.X = (g_Console.getConsoleSize().X / 2) + x;
	c.Y = (g_Console.getConsoleSize().Y / 2) - y;
	if (c.X >= 0 && c.X <= g_Console.getConsoleSize().X && 
		c.Y >= 0 && c.Y <= g_Console.getConsoleSize().Y)
		g_Console.writeToBuffer(c, ' ', color);
}

void initCamera()
{
	camera = new Matrix(4, 4);
}

void initObject()
{
	objects = new Object*[numberOfObjects];
	for (int i = 0; i < numberOfObjects; ++i) {
		objects[i] = new Object("Cube.txt");
		objects[i]->color = 0xD0;
		objects[i]->translate(2 * (rand() % 10) * (rand() % 2 * 2 - 1), x);
		objects[i]->translate(2 * (rand() % 10) * (rand() % 2 * 2 - 1), y);
		//objects[i]->translate(2 * (rand() % 5) * (rand() % 2 * 2 - 1), z);
		objects[i]->translate(-2, z);
	}
}

/*
void initPlayer()
{
	player = new Object("Cube.txt");
	player->color = 0xF0;
	player->translate(2 * (rand() % 10) * (rand() % 3 - 1), x);
	player->translate(2 * (rand() % 5) * (rand() % 3 - 1), y);
	player->translate(2 * (rand() % 5) * (rand() % 3 - 1), z);
	player->scale(5);
}
*/