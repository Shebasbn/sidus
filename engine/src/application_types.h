/* date = May 23rd 2026 5:01 pm */

#ifndef APPLICATION_TYPES_H
#define APPLICATION_TYPES_H

typedef B8 (*GameInit)(struct Game* game_inst);
typedef B8 (*GameUpdate)(struct Game* game_inst, F32 delta_time);
typedef B8 (*GameRender)(struct Game* game_inst, F32 delta_time);
typedef void (*GameOnResize)(struct Game* game_inst, U32 width, U32 height);

/*typedef struct Game Game;*/
struct Game
{
    GameInit initialize;
    GameUpdate update;
    GameRender render;
    GameOnResize on_resize;
    void* state;
};

#endif //APPLICATION_TYPES_H
