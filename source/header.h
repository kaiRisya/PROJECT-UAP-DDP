#include "stat.h"
#include "dialog.h"
#include <unistd.h>
#include <iostream>
#include <random>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;


void playmusic(const char * musicFile, DWORD flags = SND_ASYNC | SND_LOOP) {
  PlaySound(TEXT(musicFile), NULL, flags);
}

void stopmusic() {
  PlaySound(NULL, 0, SND_PURGE);
}

void print_menu(WINDOW * menu_win, int pilihanTerpilih, const char * opsi[], int jumlahopsi) {
  for (int i = 0; i < jumlahopsi; ++i) {
    if (i == pilihanTerpilih) {
      wattron(menu_win, A_REVERSE);
    }

    mvwprintw(menu_win, i + 1, 1, opsi[i]);

    if (i == pilihanTerpilih) {
      wattroff(menu_win, A_REVERSE);
    }
  }

  wrefresh(menu_win);
}

// function untuk battle

void playerturn() {
  initscr();
  clear();
  noecho();
  cbreak();

  int awalx = 20, awaly = 30;
  int lebar = 30, tinggi = 20;

  WINDOW * menu_win = newwin(tinggi, lebar, awaly, awalx);

  keypad(menu_win, TRUE);

  const char * opsi[] = {
    "Attack",
    "Magic",
    "Defense"
  };

  int jumlahopsi = sizeof(opsi) / sizeof(char * );
  int pilihanTerpilih = 0;
  int pilihan = -1;

  curs_set(0);
  while (1) {
    mvwprintw(menu_win, 0, 0, "Pilih Strategimu !!!");
    print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi);

    int tombol = wgetch(menu_win);

    switch (tombol) {
    case KEY_UP:
      if (pilihanTerpilih == 0) {
        pilihanTerpilih = jumlahopsi - 1;
      } else {
        --pilihanTerpilih;
      }
      break;

    case KEY_DOWN:
      if (pilihanTerpilih == jumlahopsi - 1) {
        pilihanTerpilih = 0;
      } else {
        ++pilihanTerpilih;
      }
      break;

    case 10:
      pilihan = pilihanTerpilih;
      break;
    }

    clrtoeol();
    refresh();

    if (pilihan == 0) {
      specialtracker = 0;
      choicesinfo();
      break;
    } else if (pilihan == 1) {
      specialtracker = 1;
      choicesinfo();
      break;
    } else if (pilihan == 2) {
      specialtracker = 2;
      break;
    }
  }

}

//login
void singIn();
void singUp();
void opsiPlay();

void opsiLogin(){
    initscr();
    clearScreen();
    noecho();
    cbreak();
    curs_set(0);

    boxMenu();
    while (true)
	{
		char jawab = getch();
		if (jawab == '1')
		{
			singIn();
			break;
		}
		else if (jawab == '2')
		{
			singUp();
			singIn();
			break;
		}
		else if (jawab == '3')
		{
			system("cls");
			exit(0);
		}
	}

    endwin();
}

void singIn(){
    curs_set(1);
    nocbreak();
    echo();
    boxSignIn();

    char username[30], password[30];
    mvprintw(13,57,"");
    getnstr(&username[0], 30);
    mvprintw(16,57,"");
    getnstr(&password[0], 30);

    ifstream akun;
    string inputUsername, inputPassword;
    akun.open("data/akunUser.txt");
    bool approve = false;
    while (akun >> inputUsername >> inputPassword)
    {
        if(inputUsername == username && inputPassword == password){
            approve = true;
            break;
        }
    }

    if(approve){
        clearScreen();
        loadingAuto(48,15);
        Sleep(100);
        clearScreen();
        loginDoneText();
        pressKey(48,24);
        clearScreen();
        opsiPlay();
    }
    else if(!approve){
        clearScreen();
        loadingAuto(48,15);
        Sleep(100);
        clearScreen();
        mvprintw(7,36,"USERNAME ATAU PASSWORD YANG ANDA MASUKKAN SALAH");
        singIn();

    }
    akun.close();
}

void singUp (){
    curs_set(1);
    nocbreak();
    echo();
    boxSignUp();

    ofstream akun;
    char username[30];
    char password[30];
    mvprintw(13, 57, "");
    getnstr(&username[0], 30);
    mvprintw(16,57,"");
    getnstr(&password[0], 30);
    akun.open("data/akunUser.txt", ios::app);
    akun << username << " " << password << endl;
    akun.close();
}

void opsiPlay(){
    curs_set(0);
    noecho();
    cbreak();
    introframe();
    mvprintw(22,10,"");
    char ch = getch();
    if(ch == 'm' || ch == 'M'){
        clearScreen();
        loadingAuto(10,10);
        printw("game akan dimulai");
        //play game
    }
    if(ch == 'b' || ch == 'B'){
        clearScreen();
        curs_set(1);
        echo();
        nocbreak();
        opsiLogin();
    }
}