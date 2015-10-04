// Marial Gutierrez
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 500
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

double x_velocity = 1.4;
double y_velocity = -2.0;

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // SCORE
        updateScoreboard(window,label,points);  
        
        // BALL
        /* BOUNCING */
        move(ball, x_velocity, y_velocity);
        pause(10);
        
        // MOUSE EVENT
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            /* if mouse was moved */
            if (getEventType(event) == MOUSE_MOVED)
            {
                /*move paddle were mouse goes */
                double x = getX(event) - getWidth(paddle) / 2;
                double y = 400;
                setLocation(paddle, x, y);
            }
        }
        
        /* Collision */
        /* ball touching paddle */
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            if (object == paddle)
            {
                y_velocity = -y_velocity;
            }
            else if (object != paddle)
            {
                if (strcmp(getType(object), "GRect") == 0)
                {
                    removeGWindow(window,object);
                    y_velocity = -y_velocity;
                    points++;
                    bricks--;
                }
            }
        }
        
        /* ball touching wall on the right */
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        /* ball touching wall on the left */
        if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        /* ball touching wall on the top */
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        /* ball touching wall on the bottom */
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            setLocation(ball,190,300);
            setLocation(paddle, 190, 400);
            lives--;
            waitForClick();
        }
    }
      
    //  END MESSAGE
    if (bricks > 0)
    {
        GLabel end = newGLabel("GAME OVER!");
        setFont(end,"SandSerif-50");
        setColor(end, "BLUE");
        add(window,end);
        setLocation(end,25,300);
    }
    else if (bricks == 0)
    {
        GLabel end = newGLabel("WINNER!");
        setFont(end,"SandSerif-50");
        setColor(end, "BLUE");
        add(window,end);
        setLocation(end,25,300);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{  
    // initial Position
    int brick_vertical = 50;
         
    // ROWS
    for (int i = 0 ; i < ROWS; i++)
    {
        int brick_horizontal = 2;
        // COLUMNS
        for (int k = 0 ; k < COLS ; k++)
        {
            GRect brick = newGRect(brick_horizontal + 5, brick_vertical, 35 ,10);
            // COLOR
            if (i == 0)
            {
                setColor(brick, "PINK");
            }
            if (i == 1 || i == 3)
            {
                setColor(brick, "GREEN");
            }
            if (i == 2)
            {
                setColor(brick, "PINK");
            }
            if (i == 4)
            {
                setColor(brick, "PINK");
            }
            add(window,brick);
            setFilled(brick,true);
            brick_horizontal = brick_horizontal + 39;
        }
        brick_vertical = brick_vertical + 15;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(190, 250, RADIUS, RADIUS);
    setFilled(ball, true);
    setColor(ball, "FF00FF"); // Magenta color
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(190, 400, 50, 10);
    setFilled(paddle, true);
    setColor(paddle, "7FFFD4"); //Aquamarine
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-50");
    setLocation(label, 190, 50);
    setColor(label, "BLACK");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
 
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
