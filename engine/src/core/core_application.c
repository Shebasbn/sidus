////////////////////////////////////////////////////////////////
//~ Sebas: Application State

typedef struct ApplicationState ApplicationState;
struct ApplicationState
{
    AppHandle app;
    B8 is_running;
    B8 is_suspended;
    PlatformHandle platform;
    S16 width;
    S16 height;
    F64 last_time;
};

global B8 is_app_init = FALSE;
global ApplicationState  app_state;

////////////////////////////////////////////////////////////////
//~ Sebas: Applicaton Functions 

B8 
application_create(AppConfig* config)
{
    B8 result = FALSE;
    if (!is_app_init)
    {
        app_state.app = config->app;
        
        // NOTE(Sebas): Initialize Subsystems
        initialize_logging();
        
        // TODO(Sebas): Remove this
        SFATAL("A test message: %f", 3.14f);
        SERROR("A test message: %f", 3.14f);
        SWARN("A test message: %f", 3.14f);
        SINFO("A test message: %f", 3.14f);
        SDEBUG("A test message: %f", 3.14f);
        STRACE("A test message: %f", 3.14f);
        
        app_state.is_running = TRUE;
        app_state.is_suspended = FALSE;
        
        if (platform_startup(&app_state.platform, config->name, 
                             config->start_pos_x, config->start_pos_y, 
                             config->start_width, config->start_height))
        {
            
            if (app_state.app.app_type == APP_TYPE_GAME && 
                app_state.app.game->initialize(app_state.app.game))
            {
                Game* game = app_state.app.game;
                game->on_resize(game, app_state.width, app_state.height);
                result = TRUE;
                is_app_init = TRUE;
            }
            else
            {
                SFATAL("Failed to initialize App!.");
                result = FALSE;
            };
        }
        else
        {
            SERROR("Failed to start_up platform!.");
            result = FALSE;
        }
    }
    else
    {
        SERROR("application_create called more than one time.");
        result = FALSE;
    }
    if (result == FALSE)
    {
        SERROR("Failed to create application!");
    }
    return result;
}

B8 
application_run()
{
    SINFO(get_memory_usage_str());
    if (app_state.app.app_type == APP_TYPE_GAME)
    {
        Game* game = app_state.app.game;
        while(app_state.is_running)
        {
            if (platform_pump_messages(app_state.platform) == FALSE)
            {
                app_state.is_running = FALSE;
            }
            
            if (!app_state.is_suspended)
            {
                
                
                if (!game->update(game, (F32)0))
                {
                    SFATAL("Game update failed, shutting down.");
                    app_state.is_running = FALSE;
                    break;
                }
                
                if (!game->render(game, (F32)0))
                {
                    SFATAL("Game render failed, shutting down.");
                    app_state.is_running = FALSE;
                    break;
                }
            }
        }
    }
    else
    {
        SFATAL("App Type invalid, shutting down.");
        app_state.is_running = FALSE;
    }
    app_state.is_running = FALSE;
    platform_shutdown(app_state.platform);
    return TRUE;
}