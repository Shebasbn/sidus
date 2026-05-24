/* date = May 23rd 2026 3:50 pm */

#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

typedef struct Game Game;
typedef enum AppType AppType;
enum AppType
{
    APP_TYPE_NULL = 0,
    APP_TYPE_GAME,
    APP_TYPE_COUNT,
};

typedef struct AppHandle AppHandle;
struct AppHandle
{
    AppType app_type;
    //U64 app_size;
    union
    {
        Game* game;
    };
};

typedef struct AppConfig AppConfig;
struct AppConfig
{
    AppHandle app;
    S16 start_pos_x;
    S16 start_pos_y;
    S16 start_width;
    S16 start_height;
    char* name;
};

shared_function B8 application_create(AppConfig* config);
shared_function B8 application_run();

#endif //CORE_APPLICATION_H
