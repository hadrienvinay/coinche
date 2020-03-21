#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define DECK_SIZE 32
#define CARDS_HAND 8
#define PLAYERS_NUMBER 4
#define PIQUE 0
#define COEUR 1
#define CARREAU 3
#define TREFLE 2
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct player{
        int cards[CARDS_HAND];
        char name[DECK_SIZE];
        int active;
        int start;
    };

struct team{
    struct player player_A;
    struct player player_B;
    int score;
    int victory;
};

struct game{
    struct team team_1;
    struct team team_2;
    int limit_score;
    int score_goal;
    int atout;
    int team_playing;
    int difficulty;
};

//menu.c
int menu();

//cards.c
void cards_mix(int *cards);
void distribution(int *cards, struct game *game);
int max(int *pli, int color);
int max_atout(int *pli, int atout);
int convert(int card);
int convert_atout(int card);
void tri(struct player *player,int choix);
void order_cards(struct player *player);

//jeu.c
int jeu(SDL_Surface *screen);
void load_game(struct game *game, int score, int difficulty);
int compt(int *pli, int atout);
int possible(struct player *player, int choix, int turn,int hand_turn, int *pli, int atout);
int winner(struct game *game, int *pli);
int play(struct player *player, int atout, int *pli, int hand_turn, int turn);

//display.c
void load_board(SDL_Surface **cards);
void display_board(struct game game, SDL_Surface *screen, SDL_Surface **cards, SDL_Surface *score_1, SDL_Surface *score_2, TTF_Font *police);
void display_card(SDL_Surface *screen, SDL_Surface **cards, int card, int playing);
void display_cards(struct player player, int turn);
void display_turn(struct game game, int turn);
void display_pli(int *pli);
void pause();

//system.c
void init();
void free_screen(SDL_Surface **cards);
void free_all();

#endif // PROTOTYPES_H_INCLUDED
