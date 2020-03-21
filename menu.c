#include "prototypes.h"

int menu(){
    //create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1100, 600, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 1100x600 video: %s\n", SDL_GetError());
        return 1;
    }

    //load image
    SDL_Surface* bmp = SDL_LoadBMP("img/opening.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    int done = 0;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = 1;
                    break;
                // check for keypresses
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = 1;
                    break;
                //get mouse event
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x > 391 && event.button.x < 550 && event.button.y > 170 && event.button.y < 280){
                        jeu(screen);
                    }
                    break;
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);
        //SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        //SDL_BlitSurface(rectangle, NULL, screen, &dstrect);
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);
}
