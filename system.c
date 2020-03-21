#include "prototypes.h"

void init(){

    srand(time(NULL));
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO |SDL_INIT_AUDIO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE); // On quitte le programme
    }
    if(TTF_Init() < 0)
    {
        printf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    //set window icon
    SDL_WM_SetIcon(SDL_LoadBMP("img/icon.bmp"), NULL);
    //Set title and create color
    SDL_WM_SetCaption("Coinche Vie", NULL);

}

void free_screen(SDL_Surface **cards){
    // Libération des surfaces chargées
    for (int i = 0 ; i < DECK_SIZE + 2 ; i++)
        SDL_FreeSurface(cards[i]);
}

void free_all(){
    //TTF_CloseFont(police);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
