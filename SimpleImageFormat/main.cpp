#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

struct vector2D {
    int x;
    int y;
    void set(int X,int Y) {
        x = X;
        y = Y;
    }
};

struct rgba {
    int r;
    int g;
    int b;
    int a;
    void set(int R, int G, int B, int A) {
        r = R; g = G; b = B; a = A;
    }
};

vector2D res;

int paint()
{
    res.set(1920, 1080);
    cout << "file name: ";
    fstream image;
    {string input; cin >> input; image.open(input, ios_base::app); }
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(res.x, res.y, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            while (!done) {
                SDL_Event event;
                int mousex, mousey;
                Uint32 buttons;

                SDL_PumpEvents();

                buttons = SDL_GetMouseState(&mousex, &mousey);

                int previous_pos[2];
                if ((buttons & SDL_BUTTON_LMASK) != 0) {
                    SDL_RenderDrawPoint(renderer, mousex, mousey);
                    SDL_RenderPresent(renderer);
                    if (previous_pos[0] != mousex and previous_pos[1] != mousey) {
                        image << "0;0;0;1;" << mousex << ";" << mousey << endl;
                    }
                    previous_pos[0] = mousex; previous_pos[1] = mousey;
                }

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }

            if (renderer) {
                SDL_DestroyRenderer(renderer);
            }
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
        SDL_Quit();
        return 0;
    }
}

int reader()
{
    res.set(1920, 1080);
    cout << "file name: ";
    fstream image;
    {string input; cin >> input; image.open(input, ios::in); }
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(res.x, res.y, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            if (!image) {
                cout << "Image not found\n";
                _getch();
                exit(1);
            }
            else {
                string line;
                rgba current;
                string token;
                int data[5];
                while (getline(image,line)) {
                    int i = 0;
                    while (token != line) {
                        token = line.substr(0, line.find_first_of(";"));
                        line = line.substr(line.find_first_of(";") + 1);
                        data[i] = stoi(token.c_str());
                        i++;
                    }
                    SDL_SetRenderDrawColor(renderer, Uint8(data[0] & 0xFF), Uint8(data[1] & 0xFF), Uint8(data[2] & 0xFF), Uint8(data[3] & 0xFF));
                    SDL_RenderDrawPoint(renderer, data[4], data[5]);
                    SDL_RenderPresent(renderer);
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    cout << "ibbra";
    {string a;cin >> a;}
    return 0;
} 

int main(int argc, char* argv[]) {
    cout << "\tSimple Image Format (sif)\n(1) Open image creator\n(2) Open image viewer\n";
    {
        int input; cin >> input;
        if (input == 1) {
            paint();
        }
        else if (input == 2) {
            reader();
        }
        else {
            cout << "invalid argument";
            exit(1);
        }
    }
}