#include <stdio.h>
#include <windows.h>

/*
 * Everything written in here is pure ANSI C / C89 with a little WinAPI.
 * MinGW or MSVC should work just fine.
 */

int checkKeyStates(int keys[], short keyStates[], int lengthKeys)
{
    /*
     * The function returns nonzero if a key is pressed and zero otherwise.
     * This boolean is stored in keyPressed.
     * The keyStates array stores the values of the every individual key state.
     */

    int iter = 0;
    int keyPressed = 0;

    for (; iter < lengthKeys; iter++)
    {
        keyStates[iter] = GetKeyState(keys[iter]); /* set the state into shared array */

        if (keyStates[iter] < -126) /* TODO: SMARTER SOLUTION */
        {
            keyPressed = 1;
        }
    }

    return keyPressed;
}

int main(void)
{
    /*
     * This function stores all the needed keys and runs the loop which sets the cursor position.
     * All keys are currently hardcoded in the keys array with the corresponding virtual key codes.
     */

    POINT cursorPos = {0, 0};
    short keyStates[4] = {0, 0, 0, 0};
    int keys[4] = {
        VK_UP,
        VK_RIGHT,
        VK_DOWN,
        VK_LEFT
    };
    int xDiff, yDiff = 0;
    int velocity = 0;
    const int startingVelocity = 1;
    const int acceleration = 1;
    const int velocityLimit = 32;

    while (1) /* TODO: PUT EXCEPTION HERE */
    {
        Sleep(1); /* slow things down */

        if (checkKeyStates(keys, keyStates, 4)) /* if a key is pressed */
        {
            if (GetCursorPos(&cursorPos)) /* if getting the cursor position succeeds */
            {
                /* TODO: SMARTER SOLUTION */
                if (keyStates[0] < -126)
                    yDiff -= velocity;
                if (keyStates[2] < -126)
                    yDiff += velocity;
                if (keyStates[1] < -126)
                    xDiff += velocity;
                if (keyStates[3] < -126)
                    xDiff -= velocity;

                if (!SetCursorPos(cursorPos.x + xDiff, cursorPos.y + yDiff)) /* if settings the cursor position fails */
                {
                    puts("Setting cursor position failed!");
                }

                xDiff = 0;
                yDiff = 0;

                if (velocity != velocityLimit)
                {
                    velocity += acceleration;
                    
                    if (velocity > velocityLimit)
                    {
                        velocity = velocityLimit;
                    }
                }
            }
            else /* if getting the cursor position failed */
            {
                puts("Getting cursor position failed!");
            }
        }
        else /* if nothing is being pressed reset the velocity */
        {
            velocity = startingVelocity;
        }
    }

    return 0;
}