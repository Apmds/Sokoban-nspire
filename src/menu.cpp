#include "menu.hpp"
#include "image_manager.hpp"
#include "image_data.hpp"
#include "level_data.hpp"
#include <stdexcept>

#define LEVEL_COMPLETE_DELAY 1000 // milliseconds needed to wait after completing a level

std::unique_ptr<Menu> MainMenu::input(SDLKey sym) {
    // TODO: update properly with input
    if (sym == SDLK_RETURN) {
        return std::make_unique<LevelSelectMenu>();
    }

    return nullptr;
}

std::unique_ptr<Menu> MainMenu::update(Uint32 delta_time) {
    return nullptr;
}

void MainMenu::draw(SDL_Surface* screen) {
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 28, 43, 58));

    SDL_Surface* wall_tex = ImageManager::getTexture(image_wall);
    SDL_Surface* ground_tex = ImageManager::getTexture(image_ground);

    // Side walls
    for (int i = 0; i < 15; i++) {
        ImageManager::drawTile(wall_tex, screen, 0, i*TILE_HEIGHT);
        ImageManager::drawTile(wall_tex, screen, 19*TILE_WIDTH, i*TILE_HEIGHT);
    }

    // Title background
    for (int i = 4; i < 16; i++) {
        ImageManager::drawTile(wall_tex, screen, i*TILE_WIDTH, 2*TILE_HEIGHT);
        ImageManager::drawTile(wall_tex, screen, i*TILE_WIDTH, 6*TILE_HEIGHT);
    }
    for (int i = 3; i < 6; i++) {
        ImageManager::drawTile(wall_tex, screen, 4*TILE_WIDTH, i*TILE_HEIGHT);
        ImageManager::drawTile(wall_tex, screen, 15*TILE_WIDTH, i*TILE_HEIGHT);
    }
    for (int i = 5; i < 15; i++) {
        ImageManager::drawTile(ground_tex, screen, i*TILE_WIDTH, 3*TILE_HEIGHT);
        ImageManager::drawTile(ground_tex, screen, i*TILE_WIDTH, 4*TILE_HEIGHT);
        ImageManager::drawTile(ground_tex, screen, i*TILE_WIDTH, 5*TILE_HEIGHT);
    }

    // Title
    ImageManager::drawTexture(ImageManager::getTexture(image_title), screen, 90, 54);
    
    SDL_Flip(screen);
}

LevelSelectMenu::LevelSelectMenu() {
    this->selectionIdx = 0;
}

std::unique_ptr<Menu> LevelSelectMenu::input(SDLKey sym) {
    // TODO: update properly with input
    return nullptr;
}

std::unique_ptr<Menu> LevelSelectMenu::update(Uint32 delta_time) {
    // TODO: update
    return std::make_unique<LevelMenu>(this->selectionIdx + 1);
}

void LevelSelectMenu::draw(SDL_Surface* screen) {
    // TODO: draw the level selection
    
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 28, 43, 58));
    
    SDL_Flip(screen);
}

// Gay function bc Level does not have a default constructor
static Level loadLevel(int level_num) {
    switch (level_num) {
	    case 1:
	    	return Level(level1size.x, level1size.y, level1map, level1playerPos, level1boxes, level1storages);
	    case 2:
	    	return Level(level2size.x, level2size.y, level2map, level2playerPos, level2boxes, level2storages);
	    default:
	    	throw std::invalid_argument("Unknown level number.");
	}
}

LevelMenu::LevelMenu(int level_num) : level(loadLevel(level_num)) {
    this->complete_delay = LEVEL_COMPLETE_DELAY;
	this->font = nSDL_LoadFont(NSDL_FONT_FANTASY, 255, 255, 255);
}

LevelMenu::~LevelMenu() {
    nSDL_FreeFont(this->font);
}

std::unique_ptr<Menu> LevelMenu::input(SDLKey sym) {
    if (this->level.isCompleted()) {
        return nullptr;
    }

    switch (sym) {
	case SDLK_UP:
	case SDLK_8:
		this->level.movePlayerUp();
		break;
	case SDLK_DOWN:
	case SDLK_2:
		level.movePlayerDown();
		break;

	case SDLK_LEFT:
	case SDLK_4:
		level.movePlayerLeft();
		break;

	case SDLK_RIGHT:
	case SDLK_6:
		level.movePlayerRight();
		break;

	default:
		break;
	}

    return nullptr;
}

std::unique_ptr<Menu> LevelMenu::update(Uint32 delta_time) {
    if (this->level.isCompleted()) {
        // Time ended (unsigned so can't check if < 0)
        if (delta_time >= this->complete_delay) {
            return std::make_unique<LevelSelectMenu>();
        }
        this->complete_delay -= delta_time;
    }

    return nullptr;
}

void LevelMenu::draw(SDL_Surface* screen) {
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 184, 200, 222));
    
    this->level.draw(screen);

    // UI
    //int framerate = delta_time == 0 ? 0 : int(1.0f/(float(delta_time)*0.001));

    if (this->level.isCompleted()) {
        nSDL_DrawString(screen, this->font, 60, 120, "\x1 \x1 Yay, the level is completed! \x1 \x1");
    }
    
    SDL_Flip(screen);
}
