typedef struct POS {
    int x;
    int y;
    int ID;
    int ENABLED;
} POS;

typedef struct vec2 {
    int x;
    int y;
} vec2;

POS* init_snake_path() {
    POS* MAP = (POS *) malloc(TILE_COUNT * sizeof(POS));
    int loop = 0;
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            MAP[loop] = (POS) {.x = x, .y = y, .ID = -1, .ENABLED = 0};
            loop += 1;
        }
    }
    return MAP;
}

void update_tile(POS* SNAKE_MAP, vec2 pos) {
    int latest_enabled_id = 0;
    for (int i = 0; i < TILE_COUNT; i++) {
        if (SNAKE_MAP[i].ENABLED == 1 && SNAKE_MAP[i].ID > latest_enabled_id)
        latest_enabled_id = SNAKE_MAP[i].ID;
        if (SNAKE_MAP[i].x == pos.x && SNAKE_MAP[i].y == pos.y) {
            SNAKE_MAP[i].x = pos.x;
            SNAKE_MAP[i].y = pos.y;
            SNAKE_MAP[i].ID = latest_enabled_id;
            SNAKE_MAP[i].ENABLED = 1;
            break;
        }
    }
}

void draw_tiles(POS* SNAKE_MAP, SDL_Renderer* renderer) {
    for (int i = 0; i < TILE_COUNT; i++) {
        if (SNAKE_MAP[i].ENABLED == 0)
            continue;
        SDL_Rect rect;
        rect.x = SNAKE_MAP[i].x;
        rect.y = SNAKE_MAP[i].y;
        rect.w = 10;
        rect.h = 10;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

int move_snake(POS* SNAKE_MAP, vec2 vec, vec2* head_pos, int* SNAKE_LENGTH) {
    int latest_enabled_id = 0;
    for (int i = 0; i < TILE_COUNT; i++) {
        if (SNAKE_MAP[i].ID > latest_enabled_id)
            latest_enabled_id = SNAKE_MAP[i].ID;
    }
    for (int i = 0; i < TILE_COUNT; i++) {
        if (SNAKE_MAP[i].ID < latest_enabled_id - *SNAKE_LENGTH - 1)
            SNAKE_MAP[i].ENABLED = 0;
    }

    for (int i = 0; i < TILE_COUNT; i++) {
        if (SNAKE_MAP[i].x==head_pos->x+vec.x&&SNAKE_MAP[i].y==head_pos->y+vec.y) {
            if (SNAKE_MAP[i].ENABLED == 1) {
                return -1;
            } else {
                SNAKE_MAP[i].ENABLED = 1;
                SNAKE_MAP[i].ID = latest_enabled_id + 1;
                head_pos->x += vec.x;
                head_pos->y += vec.y;
                return 1;
            }
        }
    }
    return -1;
}

vec2 spawn_orb(POS* SNAKE_MAP) {  
    for (int i = 0; i < TILE_COUNT; i++) {
        if (rand() < 0.2 && SNAKE_MAP[i].ENABLED == 0)
            return (vec2) {roundf(10 * SNAKE_MAP[i].x)/10, roundf(10 * SNAKE_MAP[i].x)/10};
    }
}
