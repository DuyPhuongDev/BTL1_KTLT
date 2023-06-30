#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void event1to5(int& HP, int& level,int& phoenixdown, int& rescue, int eventCode, int MaxHP,int levelO);
void read_file(string file_input, string &mapcode, string &namefile,int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown);
void xulyfile(string mapcode, int *map, int &distmap);
void levelboss(int &levelO, int i);
void event1to5(int& HP, int& level,int& phoenixdown, int& rescue, int eventCode, int MaxHP,int levelO, int &small, int &frog);
void endgame(int &rescue, int HP, int stmap, int distmap);
void shaman(int& HP, int& level,int& remedy, int eventCode, int MaxHP,int levelO,int &small,int const_remedy);
void tihon(int &HP, int MaxHP, int &remedy,int &small, int const_remedy);
void time_small(int &small,int &phoenixdown, int &HP, int MaxHP,int &count1);
void siren_vajsh(int HP, int& level,int& maidenkiss, int eventCode, int MaxHP,int levelO,int &frog, int &nholevel);
void in_frog(int &level,int &maidenkiss, int &frog, int &nholevel);
void time_frog(int &frog,int &level,int &phoenixdown,int &count2,int nholevel);
void mushmario(int &HP, int MaxHP, int level, int phoenixdown);
int nguyenTo(int n);
int fibonacci(int n);
void mushfibo(int &HP);
int king_arthur(int MaxHP);
int lancelot(int MaxHP);
void browser(int HP, int &level, int &rescue);
void MushGhost(string file_mush_ghost,int eventcode,int &HP,int MaxHP, int &phoenixdown,int &rescue);
void split_namefile(string namefile,string &file_mush_ghost,string &file_merlin_pack,string &file_aclepius_pack);
void mush_ghost_1(int arr[],int n2,int &HP);
void mush_ghost_2(int arr[],int n2,int &HP);
void mush_ghost_3(int *arr,int n2,int &HP);
void mush_ghost_4(int arr[],int n2,int &HP);
void Asclepius(string file_aclepius_pack, int &remedy, int &maidenkiss, int &phoenixdown);
void merlin(string file_merlin_pack, int &HP, int MaxHP);
bool check_pack(string merlin_name, string item_name);
#endif // __KNIGHT_H__