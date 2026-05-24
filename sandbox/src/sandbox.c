#include <core\core_base.h>
#include <core\core_application.h>
#include <core\core_logger.h>
#include <core\core_memory.h>
#include <application_types.h>
#include <entry_point.h>

#include "game.h"


#include "game.c"



B8 create_game(AppConfig* out_config)
{
    out_config->start_pos_x = 100;
    out_config->start_pos_y = 100;
    out_config->start_width = 1280;
    out_config->start_height = 720;
    out_config->name = "Sidus Engine - Sandbox";
    out_config->app.app_type = APP_TYPE_GAME;
    out_config->app.game->initialize = game_initialize;
    out_config->app.game->update = game_update;
    out_config->app.game->render = game_render;
    out_config->app.game->on_resize = game_on_resize;
    
    out_config->app.game->state = sallocate(sizeof(GameState), MEMORY_TAG_APPLICATION);
    return TRUE;
};