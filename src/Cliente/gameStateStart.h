#ifndef _GAMESTATESTART_H_
#define _GAMESTATESTART_H_

#include "gameState.h"
#include "Renderer.h"
#include "../Comun/mutex.h"
#include "../Comun/socket.h"
#include "receiver.h"
#include "window.h"
#include "music.h"

class gameStateStart: public GameState{
    private:
        std::pair<int,std::string> &playerData;
        /// variables tecnicas
        Window *window;
        Renderer *renderer;
        Socket *skt;
        Mutex mutex;
        Receiver *receiver;
        ///

        /// Manejo del flujo
        void updateInput(bool *running);
        void mainLoop();
        void cap_framerate(const Uint32 &starting_tick);
        ///
        void loadHUD();
        void render();

        /// Teclas
        bool up;
        bool down;
        bool left;
        bool right;
        bool jump;
        bool shoot;
        /// Estados
        bool quit;
        bool victory;
        bool ko;
        Music music;
    public:
        gameStateStart(Window *window, Renderer *renderer, Socket *skt,
                        std::pair<int,std::string> &playerData,
                        int level);
        void load(int level = 0);
        int unload();
        StateCode update();
        ~gameStateStart();
};


#endif // _GAMESTATESTART_H_
