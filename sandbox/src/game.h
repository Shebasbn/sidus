/* date = May 23rd 2026 7:27 pm */

#ifndef GAME_H
#define GAME_H

typedef struct GameState GameState;
struct GameState
{
    F32 delta_time;
};

B8 game_initialize(Game* game);
B8 game_update(Game* game, F32 delta_time);
B8 game_render(Game* game, F32 delta_time);
void game_on_resize(Game* game, U32 width, U32 height);


#endif //GAME_H
