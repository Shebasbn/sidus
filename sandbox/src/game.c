B8 game_initialize(Game* game)
{
    SDEBUG("game_initialized() called!");
    UnusedVariable(game);
    return TRUE;
}

B8 game_update(Game* game, F32 delta_time)
{
    /*SDEBUG("game_update() called!");*/
    UnusedVariable(game);
    UnusedVariable(delta_time);
    return TRUE;
}

B8 game_render(Game* game, F32 delta_time)
{
    /*SDEBUG("game_render() called!");*/
    UnusedVariable(game);
    UnusedVariable(delta_time);
    return TRUE;
}

void game_on_resize(Game* game, U32 width, U32 height)
{
    SDEBUG("game_resize() called!");
    UnusedVariable(game);
    UnusedVariable(width);
    UnusedVariable(height);
}