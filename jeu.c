#include "prototypes.h"

void load_game(struct game *game, int score, int difficulty){
    struct player player_North, player_South, player_East, player_West;
    struct team team_1, team_2;
    strcpy(player_North.name,"North");
    strcpy(player_South.name,"South");
    strcpy(player_East.name,"East");
    strcpy(player_West.name,"West");
    player_North.active = 1;
    player_North.start  = 1;
    player_South.active = 0;
    player_South.start  = 0;
    player_East.active  = 0;
    player_East.start   = 0;
    player_West.active  = 0;
    player_West.start   = 0;

    team_1.score    = 0;
    team_1.victory  = 0;
    team_1.player_A = player_North;
    team_1.player_B = player_South;

    team_2.score    = 0;
    team_2.victory  = 0;
    team_2.player_A = player_East;
    team_2.player_B = player_West;

    game->team_1       = team_1;
    game->team_2       = team_2;
    game->limit_score  = score;
    game->atout        = COEUR;
    game->score_goal   = 80;
    game->team_playing = 1;
    game->difficulty   = difficulty;
}

int compt(int *pli, int atout){
    int compt = 0;
    for(int i=0; i<PLAYERS_NUMBER;i++){
        //Cas d'un 9 d'atout
        if(pli[i]%8 == 2 && pli[i]/8 == atout){
            compt = compt + 14;
        }
        //Cas d'un 10
        else if(pli[i]%8 == 3){
            compt = compt + 10;
        }
        //Cas d'un Valet
        else if(pli[i]%8 == 4){
            if(pli[i]/8 == atout){
                compt = compt + 20;
            }
            else{
                compt = compt + 2;
            }
        }
        //Cas d'une Dame
        else if(pli[i]%8 == 5){
            compt = compt + 3;
        }
        //Cas d'un Roi
        else if(pli[i]%8 == 6){
            compt = compt + 4;
        }
        //Cas d'un As
        else if(pli[i]%8 == 7){
            compt = compt + 11;
        }
    }
    return compt;
}

int winner(struct game *game, int *pli){
    int winner=0;
    int card_value = 0;
    int start_player = 0;
    if(game->team_1.player_A.start){
        start_player = 1;
    }
    else if(game->team_2.player_A.start){
        start_player = 2;
    }
    else if(game->team_1.player_B.start){
        start_player = 3;
    }
    else if(game->team_2.player_B.start){
        start_player = 4;
    }
    //if atout first played get max atout played
    if(pli[0]/8 == game->atout){
        printf("Atout check winner \n");
        card_value = max_atout(pli,game->atout);
        if(convert_atout(pli[0]) == card_value){
            winner = start_player;
        }
        else if(convert_atout(pli[1]) == card_value){
            winner = start_player + 1;
        }
        else if(convert_atout(pli[2]) == card_value){
            winner = start_player + 2;
        }
        else if(convert_atout(pli[3]) == card_value){
            winner = start_player + 3;
        }
    }
    else{
        card_value = max_atout(pli,game->atout);
        //if atout played : cut
        if(card_value != -1){
            printf("CUT \n");
            if(convert_atout(pli[1]) == card_value){
            winner = start_player + 1;
            }
            else if(convert_atout(pli[2]) == card_value){
                winner = start_player + 2;
            }
            else if(convert_atout(pli[3]) == card_value){
                winner = start_player + 3;
            }
        }
        //else check higher card of the color
        else{
            card_value = max(pli,pli[0]/8);
            if(convert(pli[0]) == card_value){
            winner = start_player;
            }
            else if(convert(pli[1]) == card_value){
                winner = start_player + 1;
            }
            else if(convert(pli[2]) == card_value){
                winner = start_player + 2;
            }
            else if(convert(pli[3]) == card_value){
                winner = start_player + 3;
            }
        }
    }

    if(winner > 4){
        winner = winner - 4;
    }

    display_pli(pli);
    printf("Le player %d a gagné le tour\n",winner);
    //reset variable
    game->team_1.player_A.active = 0;
    game->team_1.player_A.start  = 0;
    game->team_1.player_B.active = 0;
    game->team_1.player_B.start  = 0;
    game->team_2.player_A.active = 0;
    game->team_2.player_A.start  = 0;
    game->team_2.player_B.active = 0;
    game->team_2.player_B.start  = 0;

    return winner;
}

int possible(struct player *player, int choix, int turn, int hand_turn, int *pli, int atout){
    //if first turn
    if (hand_turn == 0){
        pli[hand_turn] = player->cards[choix];
        return 1;
    }
    int nb_atout=0,nb_pique=0,nb_coeur=0,nb_carreau=0,nb_trefle=0;
    for(int i=0;i<CARDS_HAND-turn;i++){
        if(player->cards[i]/8 == PIQUE){
            nb_pique++;
        }
        else if(player->cards[i]/8 == COEUR){
            nb_coeur++;
        }
        else if(player->cards[i]/8 == CARREAU){
            nb_carreau++;
        }
        else if(player->cards[i]/8 == TREFLE){
            nb_trefle++;
        }
    }
    if(atout == PIQUE){
        nb_atout = nb_pique;
    }else if (atout == COEUR){
        nb_atout = nb_coeur;
    }else if (atout == CARREAU){
        nb_atout = nb_carreau;
    }else if (atout == TREFLE){
        nb_atout = nb_trefle;
    }
    //Switch first card played
    switch(pli[0]/8){
        case PIQUE:
            //if atout, check if superior possible
            if(PIQUE == atout){
                if(nb_atout){
                    if(player->cards[choix]/8 == PIQUE){
                        //if only one atout left : play it
                        if(nb_atout == 1){
                            return 1;
                        }
                        //if many atout, check if superior
                        else if(convert_atout(player->cards[choix]) > max_atout(pli,atout)){
                            return 1;
                        }
                        else{
                            //check if player have an higher atout
                            for(int i=0; i<CARDS_HAND-turn;i++){
                                if(i != choix && player->cards[i]/8 == PIQUE){
                                    if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                        printf("Vous devez monter à l'atout ! \n");
                                        return 0;
                                    }
                                }
                            }
                            return 1;
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    return 1;
                }
            }
            //si pique non atout et pique dans la main, ok
            else if(nb_pique){
                if(player->cards[choix]/8 == PIQUE){
                    return 1;
                }
                else return 0;
            }
            //si pas de pique, et des atouts, coupe
            else if (nb_atout){
                if(player->cards[choix]/8 == atout){
                    return 1;
                }
                else return 0;
            }
            //sinon pisse
            else return 1;
            break;
        case COEUR:
            if(COEUR == atout){
                if(nb_atout){
                    if(player->cards[choix]/8 == COEUR){
                        //if only one atout left : play it
                        if(nb_atout == 1){
                            return 1;
                        }
                        //if many atout, check if superior
                        else if(convert_atout(player->cards[choix]) > max_atout(pli,atout)){
                            return 1;
                        }
                        else{
                            //check if player have an higher atout
                            for(int i=0; i<CARDS_HAND-turn;i++){
                                if(i != choix && player->cards[i]/8 == COEUR){
                                    if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                        printf("Vous devez monter à l'atout ! \n");
                                        return 0;
                                    }
                                }
                            }
                            return 1;
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    return 1;
                }
            }
            else if(nb_coeur){
                if(player->cards[choix]/8 == COEUR){
                    return 1;
                }
                else return 0;
            }
            else if (nb_atout){
                if(player->cards[choix]/8 == atout){
                    return 1;
                }
                else return 0;
            }
            else return 1;
            break;
        case CARREAU:
            if(CARREAU == atout){
                if(nb_atout){
                    if(player->cards[choix]/8 == CARREAU){
                        //if only one atout left : play it
                        if(nb_atout == 1){
                            return 1;
                        }
                        //if many atout, check if superior
                        else if(convert_atout(player->cards[choix]) > max_atout(pli,atout)){
                            return 1;
                        }
                        else{
                            //check if player have an higher atout
                            for(int i=0; i<CARDS_HAND-turn;i++){
                                if(i != choix && player->cards[i]/8 == CARREAU){
                                    if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                        printf("Vous devez monter à l'atout ! \n");
                                        return 0;
                                    }
                                }
                            }
                            return 1;
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    return 1;
                }
            }
            else if(nb_carreau){
                if(player->cards[choix]/8 == CARREAU){
                    return 1;
                }
                else return 0;
            }
            else if (nb_atout){
                if(player->cards[choix]/8 == atout){
                    return 1;
                }
                else return 0;
            }
            else return 1;
            break;
        case TREFLE:
            if(TREFLE == atout){
                if(nb_atout){
                    if(player->cards[choix]/8 == TREFLE){
                        //if only one atout left : play it
                        if(nb_atout == 1){
                            return 1;
                        }
                        //if many atout, check if superior
                        else if(convert_atout(player->cards[choix]) > max_atout(pli,atout)){
                            return 1;
                        }
                        else{
                            //check if player have an higher atout
                            for(int i=0; i<CARDS_HAND-turn;i++){
                                if(i != choix && player->cards[i]/8 == TREFLE){
                                    if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                        printf("Vous devez monter à l'atout ! \n");
                                        return 0;
                                    }
                                }
                            }
                            return 1;
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    return 1;
                }
            }
            else if(nb_trefle){
                if(player->cards[choix]/8 == TREFLE){
                    return 1;
                }
                else return 0;
            }
            else if (nb_atout){
                if(player->cards[choix]/8 == atout){
                    return 1;
                }
                else return 0;
            }
            else return 1;
            break;
        default: return 0;
   }
}

int play(struct player *player, int atout, int *pli, int hand_turn, int turn){
    int selected_card = -1;
    int nb_atout=0,nb_pique=0,nb_coeur=0,nb_carreau=0,nb_trefle=0;
    for(int i=0;i<CARDS_HAND-turn;i++){
        if(player->cards[i]/8 == PIQUE){
            nb_pique++;
        }
        else if(player->cards[i]/8 == COEUR){
            nb_coeur++;
        }
        else if(player->cards[i]/8 == CARREAU){
            nb_carreau++;
        }
        else if(player->cards[i]/8 == TREFLE){
            nb_trefle++;
        }
    }
    if(atout == PIQUE){
        nb_atout = nb_pique;
    }else if (atout == COEUR){
        nb_atout = nb_coeur;
    }else if (atout == CARREAU){
        nb_atout = nb_carreau;
    }else if (atout == TREFLE){
        nb_atout = nb_trefle;
    }
    //Switch first card played
    switch(pli[0]/8){
        case PIQUE:
            //if atout, check if superior possible
            if(PIQUE == atout){
                if(nb_atout){
                    for(int i=0; i<CARDS_HAND-turn; i++){
                        if(player->cards[i]/8 == PIQUE){
                            //if only one atout left : play it
                            if(nb_atout == 1){
                                selected_card = i;
                            }
                            //if many atout, check if superior
                            else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                selected_card = i;
                            }
                            //else play a lower atout
                            else{
                                selected_card = i;
                            }
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    selected_card = 0;
                }
            }
            else if(nb_pique){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == PIQUE){
                        //if only one pique left : play it
                        if(nb_pique == 1){
                            selected_card = i;
                        }
                        //if many pique, check if superior
                        else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                            selected_card = i;
                        }
                        //else play a lower pique
                        else{
                            selected_card = i;
                        }
                    }
                }
            }
            //si pas de pique, et des atouts, coupe
            else if (nb_atout){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == atout){
                        selected_card = i;
                    }
                }
            }
            //sinon pisse
            else selected_card = 0;
            break;
        case COEUR:
            //if atout, check if superior possible
            if(COEUR == atout){
                if(nb_atout){
                    for(int i=0; i<CARDS_HAND-turn; i++){
                        if(player->cards[i]/8 == COEUR){
                            //if only one atout left : play it
                            if(nb_atout == 1){
                                selected_card = i;
                            }
                            //if many atout, check if superior
                            else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                selected_card = i;
                            }
                            //else play a lower atout
                            else{
                                selected_card = i;
                            }
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    selected_card = 0;
                }
            }
            else if(nb_pique){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == COEUR){
                        //if only one pique left : play it
                        if(nb_pique == 1){
                            selected_card = i;
                        }
                        //if many pique, check if superior
                        else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                            selected_card = i;
                        }
                        //else play a lower pique
                        else{
                            selected_card = i;
                        }
                    }
                }
            }
            //si pas de pique, et des atouts, coupe
            else if (nb_atout){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == atout){
                        selected_card = i;
                    }
                }
            }
            //sinon pisse
            else selected_card = 0;
            break;
        case CARREAU:
            //if atout, check if superior possible
            if(CARREAU == atout){
                if(nb_atout){
                    for(int i=0; i<CARDS_HAND-turn; i++){
                        if(player->cards[i]/8 == CARREAU){
                            //if only one atout left : play it
                            if(nb_atout == 1){
                                selected_card = i;
                            }
                            //if many atout, check if superior
                            else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                selected_card = i;
                            }
                            //else play a lower atout
                            else{
                                selected_card = i;
                            }
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    selected_card = 0;
                }
            }
            else if(nb_pique){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == CARREAU){
                        //if only one pique left : play it
                        if(nb_pique == 1){
                            selected_card = i;
                        }
                        //if many pique, check if superior
                        else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                            selected_card = i;
                        }
                        //else play a lower pique
                        else{
                            selected_card = i;
                        }
                    }
                }
            }
            //si pas de pique, et des atouts, coupe
            else if (nb_atout){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == atout){
                        selected_card = i;
                    }
                }
            }
            //sinon pisse
            else selected_card = 0;
            break;
        case TREFLE:
            //if atout, check if superior possible
            if(TREFLE == atout){
                if(nb_atout){
                    for(int i=0; i<CARDS_HAND-turn; i++){
                        if(player->cards[i]/8 == TREFLE){
                            //if only one atout left : play it
                            if(nb_atout == 1){
                                selected_card = i;
                            }
                            //if many atout, check if superior
                            else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                                selected_card = i;
                            }
                            //else play a lower atout
                            else{
                                selected_card = i;
                            }
                        }
                    }
                }
                //if no atout, play whatever
                else{
                    selected_card = 0;
                }
            }
            else if(nb_pique){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == TREFLE){
                        //if only one pique left : play it
                        if(nb_pique == 1){
                            selected_card = i;
                        }
                        //if many pique, check if superior
                        else if(convert_atout(player->cards[i]) > max_atout(pli,atout)){
                            selected_card = i;
                        }
                        //else play a lower pique
                        else{
                            selected_card = i;
                        }
                    }
                }
            }
            //si pas de pique, et des atouts, coupe
            else if (nb_atout){
                for(int i=0; i<CARDS_HAND-turn; i++){
                    if(player->cards[i]/8 == atout){
                        selected_card = i;
                    }
                }
            }
            //sinon pisse
            else selected_card = 0;
            break;
    }

    if(selected_card == -1){
        selected_card = 0;
    }

    return selected_card;
}

int jeu(SDL_Surface *screen)
{
    //cards surfaces : tab[33] -> 34 values
    SDL_Surface *cards_screen[DECK_SIZE+1] = {NULL};
    SDL_Surface *score_1, *score_2 = NULL;
    //SDL_Surface *players[PLAYERS_NUMBER-1] = {NULL};

    TTF_Font *police = NULL;
    police = TTF_OpenFont("img/calibri.ttf", 20);

    int cards[DECK_SIZE-1];
    int difficulty = 0;
    int limit_score = 1000;

    struct game game;
    load_game(&game, limit_score, difficulty);

    //game variables
    int turn = 0, hand_turn = 0, manche = 0, start_player = 1, score_team_1 = 0, score_team_2 = 0;
    int pli[PLAYERS_NUMBER];
    int selected_card=0;
    load_board(cards_screen);
    //game loop
    while (game.team_1.score < game.limit_score || game.team_2.score < game.limit_score)
    {
        //cards mix
        cards_mix(cards);
        //cards distribution and ordering
        distribution(cards,&game);
        order_cards(&game.team_1.player_A);
        order_cards(&game.team_2.player_A);
        order_cards(&game.team_1.player_B);
        order_cards(&game.team_2.player_B);

        display_board(game, screen, cards_screen, score_1, score_2, police);
        //Annonce turn
        //annonce();
        //round loop

        while (turn < CARDS_HAND)
        {
            SDL_Delay(1000);
            //player one: NORTH playing
            if(game.team_1.player_A.active){
                int continuer = 1;
                int choix = 0;
                SDL_Event event;
                while (continuer)
                {
                    SDL_WaitEvent(&event);
                    switch(event.type)
                    {
                        case SDL_QUIT:
                            continuer = 0;
                        case SDL_MOUSEBUTTONUP:
                            if(event.button.x > (screen->w - 820) && event.button.x < (screen->w - 340) && event.button.y > (screen->h - 164) && event.button.y < (screen->h - 2)){
                                choix = (event.button.x - 280)/60;
                                if(possible(&game.team_1.player_A,choix,turn,hand_turn,pli,game.atout)){
                                    display_card(screen, cards_screen, game.team_1.player_A.cards[choix], 1);
                                    pli[hand_turn] = game.team_1.player_A.cards[choix];
                                    tri(&game.team_1.player_A,choix);
                                    game.team_1.player_A.active = 0;
                                    game.team_2.player_A.active = 1;
                                    hand_turn++;
                                    continuer = 0;
                                }
                                else{
                                    printf("Vous ne pouvez pas jouer cette carte !\n");
                                }
                            }
                            else {
                                printf("Mauvaise sélection de carte, Réessaye !\n");
                            }
                    }
                }

            }
            //Player 2: EAST playing
            else if(game.team_2.player_A.active){
                selected_card = play(&game.team_2.player_A, game.atout, pli, hand_turn,turn);
                display_card(screen, cards_screen, game.team_2.player_A.cards[selected_card], 2);
                pli[hand_turn] = game.team_2.player_A.cards[selected_card];
                tri(&game.team_2.player_A,selected_card);
                game.team_2.player_A.active = 0;
                game.team_1.player_B.active = 1;
                hand_turn++;
            }
            //Player 3: SOUTH playing
            else if(game.team_1.player_B.active){
                selected_card = play(&game.team_1.player_B, game.atout, pli, hand_turn,turn);
                display_card(screen, cards_screen, game.team_1.player_B.cards[selected_card], 3);
                pli[hand_turn] = game.team_1.player_B.cards[selected_card];
                tri(&game.team_1.player_B,selected_card);
                game.team_1.player_B.active = 0;
                game.team_2.player_B.active = 1;
                hand_turn++;
            }

            //Player 4: WEST playing
            else if(game.team_2.player_B.active){
                selected_card = play(&game.team_2.player_B, game.atout, pli, hand_turn,turn);
                display_card(screen, cards_screen, game.team_2.player_B.cards[selected_card], 4);
                pli[hand_turn] = game.team_2.player_B.cards[selected_card];
                tri(&game.team_2.player_B,selected_card);
                game.team_2.player_B.active = 0;
                game.team_1.player_A.active = 1;
                hand_turn++;
            }
            //end of a hand, calcul score  and winner
            if(hand_turn >= 4){
                //score incrementation and next starter
                start_player = winner(&game, pli);
                switch (start_player){
                    case 1:
                        game.team_1.player_A.active = 1;
                        game.team_1.player_A.start = 1;
                        score_team_1 += compt(pli,game.atout);
                        if(turn == 7){
                            score_team_1 += 10;
                        }
                        break;
                    case 2:
                        game.team_2.player_A.active = 1;
                        game.team_2.player_A.start = 1;
                        score_team_2 += compt(pli,game.atout);
                        if(turn == 7){
                            score_team_2 += 10;
                        }
                        break;
                    case 3:
                        game.team_1.player_B.active = 1;
                        game.team_1.player_B.start = 1;
                        score_team_1 += compt(pli,game.atout);
                        if(turn == 7){
                            score_team_1 += 10;
                        }
                        break;
                    case 4:
                        game.team_2.player_B.active = 1;
                        game.team_2.player_B.start = 1;
                        score_team_2 += compt(pli,game.atout);
                        if(turn == 7){
                            score_team_2 += 10;
                        }
                        break;
                    default:
                        printf("Error end of turn: start player : %d\n",start_player);
                        game.team_1.player_A.active = 1;
                        game.team_1.player_A.start = 1;
                        break;
                }
                printf("\nEND OF TURN\n");
                turn++;
                pli[0]=-1;
                pli[1]=-1;
                pli[2]=-1;
                pli[3]=-1;
                hand_turn = 0;
            }
        }
        //end of a round update team score
        printf("Manche %d terminée\n",manche);
        if(game.team_playing == 1){
           if(score_team_1 >= game.score_goal){
                game.team_1.score += game.score_goal;
                printf("L'équipe UNE a rempli son contract : %d %d\n",game.score_goal,game.atout);
           }
           else{
                game.team_2.score += 160;
                printf("L'équipe UNE a chute après avoir annoncé : %d %d\n",game.score_goal,game.atout);
           }
        }
        else if (game.team_playing == 2){
            if(score_team_2 >= game.score_goal){
                game.team_2.score += game.score_goal;
                printf("L'équipe DEUX a rempli son contract : %d %d\n",game.score_goal,game.atout);
            }
            else{
                game.team_1.score += 160;
                printf("L'équipe DEUX a chuté après avoir annoncé : %d %d\n",game.score_goal,game.atout);
           }
        }
        //next turn incrementation and reset
        turn = 0;
        manche++;
    }
    free_screen(cards_screen);
    //End game message
    if(game.team_1.score >= game.limit_score){
        printf("Vous avez gagné la partie ! BRAVO :D \n");
        printf("Team UNE : %d -- Team DEUX : %d \n",game.team_1.score,game.team_2.score);
    }
    else if(game.team_1.score >= game.limit_score){
        printf("Vous avez perdu :( LOOOOSER !\n");
        printf("Team UNE : %d -- Team DEUX : %d \n",game.team_1.score,game.team_2.score);
    }
    else{
        printf("Erreur de score\n");
    }

    return 0;
}
