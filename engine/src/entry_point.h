/* date = May 23rd 2026 5:16 pm */

#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

extern B8 create_game(AppConfig* out_config);

int main()
{   
    initialize_memory();
    int result = 0;
    Game game = {};
    AppConfig config = {};
    config.app.game = &game;
    if (create_game(&config))
    {
        if (game.render && game.update && game.initialize && game.on_resize)
        {
            if (application_create(&config))
            {
                if (!application_run())
                {
                    SINFO("Applictain did not shutdown gracefully.");
                }
            }
            else
            {
                SINFO("Could not create Application!!");
                result = -3;
            }
        }
        else
        {
            SFATAL("The game's function pointers must be assigned!");
            result = -2;
        }
    }
    else
    {
        SFATAL("Could not create game!");
        result = -1;
    }
    shutdown_memory();
    return result;
}

#endif //ENTRY_POINT_H
