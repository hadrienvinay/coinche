#include "prototypes.h"

//cards mix
void cards_mix(int *cards){
    int cards_temp[DECK_SIZE];
    int mix, alea = 0;

    for (int i=0; i<DECK_SIZE; i++){
        cards[i] = i;
        cards_temp[i] = i;
    }
    for (int i=0; i<DECK_SIZE; i++){
        alea = rand()%DECK_SIZE;
        if(alea < DECK_SIZE && alea > 0){
            cards_temp[i] = cards[i];
            cards[i] = cards[alea];
            cards[alea] = cards_temp[i];
            if(i == DECK_SIZE-1){
                i = 0;
                mix++;
            }
            if( mix == 5){
                break;
            }
        }
    }
}

void distribution(int *cards, struct game *game){
    for (int i=0; i<CARDS_HAND; i++){
        game->team_1.player_A.cards[i] = cards[i];
        game->team_1.player_B.cards[i] = cards[i+(CARDS_HAND)];
        game->team_2.player_A.cards[i] = cards[i+(CARDS_HAND*2)];
        game->team_2.player_B.cards[i] = cards[i+(CARDS_HAND*3)];
    }
}

void order_cards(struct player *player){
    int cards_temp[CARDS_HAND];
    int nb_pique=0,nb_coeur=0,nb_carreau=0,nb_trefle=0;
    for(int i=0;i<CARDS_HAND;i++){
        cards_temp[i] = player->cards[i];
    }
    //order by color
    for(int i=0;i<CARDS_HAND;i++){
        if(cards_temp[i]/8 == PIQUE){
            player->cards[nb_pique] = cards_temp[i];
            nb_pique++;
        }
    }
    for(int i=0;i<CARDS_HAND;i++){
        if(cards_temp[i]/8 == COEUR){
            player->cards[nb_pique+nb_coeur] = cards_temp[i];
            nb_coeur++;
        }
    }
    for(int i=0;i<CARDS_HAND;i++){
        if(cards_temp[i]/8 == CARREAU){
            player->cards[nb_pique+nb_coeur+nb_carreau] = cards_temp[i];
            nb_carreau++;
        }
    }
    for(int i=0;i<CARDS_HAND;i++){
        if(cards_temp[i]/8 == TREFLE){
            player->cards[nb_pique+nb_coeur+nb_carreau+nb_trefle] = cards_temp[i];
            nb_trefle++;
        }
    }
    //order them by value
    for(int i=0;i<CARDS_HAND;i++){
        cards_temp[i] = player->cards[i];
    }
    for(int j=1; j<nb_pique; j++){
        for(int i=0;i<nb_pique-1;i++){
            if(convert(player->cards[i]) > convert(player->cards[i+1])){
                cards_temp[i] = player->cards[i];
                player->cards[i] = player->cards[i+1];
                player->cards[i+1] = cards_temp[i];
            }
        }
    }
    for(int j=1; j<nb_coeur; j++){
        for(int i=nb_pique;i<nb_pique+nb_coeur-1;i++){
            if(convert(player->cards[i]) > convert(player->cards[i+1])){
                cards_temp[i] = player->cards[i];
                player->cards[i] = player->cards[i+1];
                player->cards[i+1] = cards_temp[i];
            }
        }
    }
    for(int j=1; j<nb_carreau; j++){
        for(int i=nb_pique+nb_coeur;i<nb_pique+nb_coeur+nb_carreau-1;i++){
            if(convert(player->cards[i]) > convert(player->cards[i+1])){
                cards_temp[i] = player->cards[i];
                player->cards[i] = player->cards[i+1];
                player->cards[i+1] = cards_temp[i];
            }
        }
    }
    for(int j=1; j<nb_trefle; j++){
        for(int i=nb_pique+nb_coeur+nb_carreau;i<nb_pique+nb_coeur+nb_carreau+nb_trefle-1;i++){
            if(convert(player->cards[i]) > convert(player->cards[i+1])){
                cards_temp[i] = player->cards[i];
                player->cards[i] = player->cards[i+1];
                player->cards[i+1] = cards_temp[i];
            }
        }
    }

}

// put the card played in last pos in the tab
void tri(struct player *player,int choix){
    int card_selected = player->cards[choix];
    for(int i=choix;i<CARDS_HAND-1;i++){
        player->cards[i] = player->cards[i+1];
    }
    player->cards[CARDS_HAND-1] = card_selected;
}


int max(int *pli, int color){
    int max = -1;
    for (int i=0; i< PLAYERS_NUMBER; i++){
        if(pli[i]/8 == color){
            switch (pli[i]%8){
                case 0:
                    if(max <= 0){max = 0;}
                    break;
                case 1:
                    if(max < 1){max = 1;}
                    break;
                case 2:
                    if(max < 2){max = 2;}
                    break;
                case 3:
                    if(max < 6){max = 6;}
                    break;
                case 4:
                    if(max < 3){max = 3;}
                    break;
                case 5:
                    if(max < 4){max = 4;}
                    break;
                case 6:
                    if(max < 5){max = 5;}
                    break;
                case 7:
                    if(max < 7){max = 7;}
                    break;
                default: break;
            }
        }
    }
    return max;
}

int convert(int card){
    switch (card%8){
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 6;
            break;
        case 4:
            return 3;
            break;
        case 5:
            return 4;
            break;
        case 6:
            return 5;
            break;
        case 7:
            return 7;
            break;
        default: return 0;
    }
}

int max_atout(int *pli, int atout){
    int max = -1;
    for (int i=0; i< PLAYERS_NUMBER; i++){
        if(pli[i]/8 == atout){
            switch (pli[i]%8){
                case 0:
                    if(max <= 0){max = 0;}
                    break;
                case 1:
                    if(max < 1){max = 1;}
                    break;
                case 2:
                    if(max < 6){max = 6;}
                    break;
                case 3:
                    if(max < 4){max = 4;}
                    break;
                case 4:
                    if(max < 7){max = 7;}
                    break;
                case 5:
                    if(max < 2){max = 2;}
                    break;
                case 6:
                    if(max < 3){max = 3;}
                    break;
                case 7:
                    if(max < 5){max = 5;}
                    break;
                default: break;
            }
        }
    }
    return max;
}

int convert_atout(int card){
    switch (card%8){
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        case 2:
            return 6;
            break;
        case 3:
            return 4;
            break;
        case 4:
            return 7;
            break;
        case 5:
            return 2;
            break;
        case 6:
            return 3;
            break;
        case 7:
            return 5;
            break;
        default: return 0;
    }
}

