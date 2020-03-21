#include "prototypes.h"

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                continuer = 0;
                break;
        }
    }
}

void load_board(SDL_Surface **cards){
     //cards load
    cards[0] = SDL_LoadBMP("img/cards/s_7.bmp");
    cards[1] = SDL_LoadBMP("img/cards/s_8.bmp");
    cards[2] = SDL_LoadBMP("img/cards/s_9.bmp");
    cards[3] = SDL_LoadBMP("img/cards/s_10.bmp");
    cards[4] = SDL_LoadBMP("img/cards/s_J.bmp");
    cards[5] = SDL_LoadBMP("img/cards/s_Q.bmp");
    cards[6] = SDL_LoadBMP("img/cards/s_K.bmp");
    cards[7] = SDL_LoadBMP("img/cards/s_1.bmp");

    cards[8] = SDL_LoadBMP("img/cards/h_7.bmp");
    cards[9] = SDL_LoadBMP("img/cards/h_8.bmp");
    cards[10]= SDL_LoadBMP("img/cards/h_9.bmp");
    cards[11] = SDL_LoadBMP("img/cards/h_10.bmp");
    cards[12] = SDL_LoadBMP("img/cards/h_J.bmp");
    cards[13] = SDL_LoadBMP("img/cards/h_Q.bmp");
    cards[14] = SDL_LoadBMP("img/cards/h_K.bmp");
    cards[15] = SDL_LoadBMP("img/cards/h_1.bmp");

    cards[16] = SDL_LoadBMP("img/cards/d_7.bmp");
    cards[17] = SDL_LoadBMP("img/cards/d_8.bmp");
    cards[18] = SDL_LoadBMP("img/cards/d_9.bmp");
    cards[19] = SDL_LoadBMP("img/cards/d_10.bmp");
    cards[20] = SDL_LoadBMP("img/cards/d_J.bmp");
    cards[21] = SDL_LoadBMP("img/cards/d_Q.bmp");
    cards[22] = SDL_LoadBMP("img/cards/d_K.bmp");
    cards[23] = SDL_LoadBMP("img/cards/d_1.bmp");

    cards[24] = SDL_LoadBMP("img/cards/c_7.bmp");
    cards[25] = SDL_LoadBMP("img/cards/c_8.bmp");
    cards[26] = SDL_LoadBMP("img/cards/c_9.bmp");
    cards[27] = SDL_LoadBMP("img/cards/c_10.bmp");
    cards[28] = SDL_LoadBMP("img/cards/c_J.bmp");
    cards[29] = SDL_LoadBMP("img/cards/c_Q.bmp");
    cards[30] = SDL_LoadBMP("img/cards/c_K.bmp");
    cards[31] = SDL_LoadBMP("img/cards/c_1.bmp");

    cards[32] = SDL_LoadBMP("img/cards/back_b.bmp");
    cards[33] = SDL_LoadBMP("img/cards/back_b2.bmp");
}

void display_board(struct game game, SDL_Surface *screen, SDL_Surface **cards, SDL_Surface *score_1, SDL_Surface *score_2, TTF_Font *police){

    char score_box_1[20] = "";
    char score_box_2[20] = "";

    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255, 255, 255};
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
    Uint32 bleuVert = SDL_MapRGB(screen->format, 17, 206, 112);

    //fond de l'écran
    SDL_FillRect(screen, NULL, bleuVert);

    //display des scores en haut à droite de l'écran
    sprintf(score_box_1, "Equipe 1 : %d", game.team_1.score);
    sprintf(score_box_2, "Equipe 2 : %d", game.team_2.score);
    score_1 = TTF_RenderText_Blended(police, score_box_1, white);
    score_2 = TTF_RenderText_Blended(police, score_box_2, white);
    SDL_Rect pos;
    pos.x = (screen->w - score_1->w) - 4;
    pos.y = 4;
    //score
    SDL_BlitSurface(score_1, 0, screen, &pos);
    pos.x = (screen->w - score_2->w) - 4;
    pos.y = 24;
    SDL_BlitSurface(score_2, 0, screen, &pos);

    //display cards for player 1
    SDL_Rect pos1, pos2, pos3, pos4;
    pos1.x = (screen->w - 820);
    pos1.y = (screen->h - 164);
    pos2.x = (screen->w - 164);
    pos2.y = (screen->h - 500);
    pos3.x = (screen->w - 820);
    pos3.y = 2;
    pos4.x = 2;
    pos4.y = (screen->h - 500);
    for(int i=0; i<CARDS_HAND;i++){
        SDL_SetColorKey(cards[game.team_1.player_A.cards[i]], SDL_SRCCOLORKEY, SDL_MapRGB(cards[game.team_1.player_A.cards[i]]->format, 163, 73, 164));
        SDL_BlitSurface(cards[game.team_1.player_A.cards[i]], 0, screen,&pos1);
        SDL_SetColorKey(cards[32], SDL_SRCCOLORKEY, SDL_MapRGB(cards[33]->format, 163, 73, 164));
        SDL_SetColorKey(cards[33], SDL_SRCCOLORKEY, SDL_MapRGB(cards[33]->format, 163, 73, 164));
        SDL_BlitSurface(cards[33], 0, screen,&pos2);
        SDL_BlitSurface(cards[32], 0, screen,&pos3);
        SDL_BlitSurface(cards[33], 0, screen,&pos4);
        pos1.x += 60;
        pos2.y += 40;
        pos3.x += 60;
        pos4.y += 40;
    }
    //update screen
    SDL_Flip(screen);


}

void update_board(struct game game, SDL_Surface *screen, SDL_Surface **cards){

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_Flip(screen);

}


void display_turn(struct game game, int turn){
    printf("----------- TOUR %d -------------\n",turn);
    display_cards(game.team_1.player_A,turn);
    display_cards(game.team_2.player_A,turn);
    display_cards(game.team_1.player_B,turn);
    display_cards(game.team_2.player_B,turn);
}

void display_card(SDL_Surface *screen, SDL_Surface **cards, int card, int playing){
    //free previous surface
    //SDL_FreeSurface(cards);
    SDL_Rect pos;
    if(playing == 1){
        pos.x = (screen->w - cards[card]->w)/2;
        pos.y = (screen->h - cards[card]->h)/2 + 60;
    }
    else if (playing == 2){
        pos.x = (screen->w - cards[card]->w)/2 + 60;
        pos.y = (screen->h - cards[card]->h)/2 ;
    }
    else if (playing == 3){
        pos.x = (screen->w - cards[card]->w)/2;
        pos.y = (screen->h - cards[card]->h)/2 - 60;
    }
    else if (playing == 4){
        pos.x = (screen->w - cards[card]->w)/2 - 60;
        pos.y = (screen->h - cards[card]->h)/2 ;
    }

    //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_BlitSurface(cards[card], 0, screen,&pos);
    SDL_Flip(screen);
}

void display_cards(struct player player, int turn){
    //Show current hand
    printf("Cartes de %s: ",player.name);
    for(int i=0;i<CARDS_HAND-turn;i++){
        if(player.cards[i] < 8){
            printf(ANSI_COLOR_BLUE);
        }
        else if(player.cards[i] < 16){
            printf(ANSI_COLOR_RED);
        }
        else if(player.cards[i] < 24){
            printf(ANSI_COLOR_MAGENTA);
        }
        else{
            printf(ANSI_COLOR_GREEN);
        }
        if(player.cards[i]%8<4){
            printf("%d " ANSI_COLOR_RESET,player.cards[i]%8 + 7);
        }
        else if (player.cards[i]%8 == 4){
           printf("V " ANSI_COLOR_RESET);
        }
        else if (player.cards[i]%8 == 5){
           printf("D " ANSI_COLOR_RESET);
        }
        else if (player.cards[i]%8 == 6){
          printf("R " ANSI_COLOR_RESET);
        }
        else if (player.cards[i]%8 == 7){
          printf("A " ANSI_COLOR_RESET);
        }
    }
    printf("\n");

}

void display_pli(int *pli){
    for(int i =0; i<PLAYERS_NUMBER; i++){
        if(pli[i] < 8){
            printf(ANSI_COLOR_BLUE);
        }
        else if(pli[i] < 16){
            printf(ANSI_COLOR_RED);
        }
        else if(pli[i] < 24){
            printf(ANSI_COLOR_MAGENTA);
        }
        else{
            printf(ANSI_COLOR_GREEN);
        }
        if(pli[i]%8<4){
            printf("%d " ANSI_COLOR_RESET,pli[i]%8 + 7);
        }
        else if (pli[i]%8 == 4){
           printf("V " ANSI_COLOR_RESET);
        }
        else if (pli[i]%8 == 5){
           printf("D " ANSI_COLOR_RESET);
        }
        else if (pli[i]%8 == 6){
          printf("R " ANSI_COLOR_RESET);
        }
        else if (pli[i]%8 == 7){
          printf("A " ANSI_COLOR_RESET);
        }
    }
    printf("\n");
}

