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

int main(int argc, char* argv[])
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
                        //cout << "number " << i  << " color " << color[i] << endl;
                        i++;
                    }
                    cout << "drawing pixel at " << data[4] << "x" << data[5] << " with color " << Uint8(data[1] & 0xFF) << Uint8(data[2] & 0xFF) << Uint8(data[3] & 0xFF);
                    SDL_SetRenderDrawColor(renderer, Uint8(data[0] & 0xFF), Uint8(data[1] & 0xFF), Uint8(data[2] & 0xFF), Uint8(data[3] & 0xFF));
                    SDL_RenderDrawPoint(renderer, data[4], data[5]);
                    SDL_RenderPresent(renderer);
                    //cout << "new pixel" << endl;
                    // finito il pixel
                }
            }

            while (!done) {
                
                SDL_Event event;
                int mousex, mousey;
                Uint32 buttons;

                SDL_PumpEvents();  // make sure we have the latest mouse state.

                buttons = SDL_GetMouseState(&mousex, &mousey);

                SDL_Log("Mouse cursor is at %d, %d", mousex, mousey);
                if ((buttons & SDL_BUTTON_LMASK) != 0) {
                    SDL_Log("Mouse Button 1 (left) is pressed.");
                }
                /*

                int y = 0;
                for (int x = 0; x < pixels.size(); x++) {
                    if (x == res.x + 1) {
                        y++;
                        x = 0;
                    }
                    SDL_SetRenderDrawColor(renderer, pixels[x].r, pixels[x].g, pixels[x].b, pixels[x].a);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
                for (int y = 0; y < res.y; y++) {
                    for (int x = 0; x < res.x; x++) {
                        SDL_RenderDrawPoint(renderer, x, y);
                    }
                }
                SDL_RenderPresent(renderer);
                */
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
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