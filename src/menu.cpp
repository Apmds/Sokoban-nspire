#include "menu.hpp"
#include "image_manager.hpp"
#include "image_data.hpp"
#include "level_data.hpp"
#include <stdexcept>

#define LEVEL_COMPLETE_DELAY 1000 // milliseconds needed to wait after completing a level
#define LEVEL_SELECT_ROW_SIZE 9
#define LEVEL_NUMS 45

MainMenu::MainMenu() {
    this->font = FontManager::loadFont(image_font, 7, 9, 225, 114, 91);
}

MainMenu::~MainMenu() {
    FontManager::unloadFont(this->font);
}

std::unique_ptr<Menu> MainMenu::input(SDLKey sym) {
    if (sym == SDLK_RETURN) {
        return std::make_unique<LevelSelectMenu>();
    }

    return nullptr;
}

std::unique_ptr<Menu> MainMenu::update(Uint32 delta_time) {
    (void)delta_time;   // Hides Wunused-parameter
    return nullptr;
}

void MainMenu::draw(SDL_Surface* screen) {
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 28, 43, 58));

    SDL_Surface* wall_tex = ImageManager::getTexture(image_wall);
    SDL_Surface* ground_tex = ImageManager::getTexture(image_ground);
    SDL_Surface* player_tex = ImageManager::getTexture(image_player);
    SDL_Surface* box_tex = ImageManager::getTexture(image_box);

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

    // Play button
    ImageManager::drawTexture(ImageManager::getTexture(image_button_long_selected), screen, 128, 124);
    FontManager::drawText(screen, this->font, 144, 132, "Play");

    // Playground
    for (int i = 7; i < 13; i++) {
        ImageManager::drawTile(wall_tex, screen, i*TILE_WIDTH, 10*TILE_HEIGHT);
        ImageManager::drawTile(wall_tex, screen, i*TILE_WIDTH, 13*TILE_HEIGHT);
    }
    for (int i = 11; i < 13; i++) {
        ImageManager::drawTile(wall_tex, screen, 7*TILE_WIDTH, i*TILE_HEIGHT);
        ImageManager::drawTile(wall_tex, screen, 12*TILE_WIDTH, i*TILE_HEIGHT);
    }
    for (int i = 8; i < 12; i++) {
        ImageManager::drawTile(ground_tex, screen, i*TILE_WIDTH, 11*TILE_HEIGHT);
        ImageManager::drawTile(ground_tex, screen, i*TILE_WIDTH, 12*TILE_HEIGHT);
    }

    // Playground actors
    ImageManager::drawTile(player_tex, screen, 8*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
    ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);

    
    SDL_Flip(screen);
}

LevelSelectMenu::LevelSelectMenu() {
    this->font = FontManager::loadFont(image_font, 7, 9, 225, 114, 91);
    this->selectionIdx = 0;
    this->invalidSelectionTime = 0;
}

LevelSelectMenu::~LevelSelectMenu() {
    FontManager::unloadFont(this->font);
}

std::unique_ptr<Menu> LevelSelectMenu::input(SDLKey sym) {
    switch (sym) {
    case SDLK_UP:
    case SDLK_8:
        this->selectionIdx = (this->selectionIdx - LEVEL_SELECT_ROW_SIZE);
        while (this->selectionIdx < 0) {
            this->selectionIdx += LEVEL_NUMS;
        }
        break;
    case SDLK_DOWN:
    case SDLK_2:
        this->selectionIdx = (this->selectionIdx + LEVEL_SELECT_ROW_SIZE) % LEVEL_NUMS;
        break;

    case SDLK_LEFT:
    case SDLK_4:
        if (this->selectionIdx % LEVEL_SELECT_ROW_SIZE == 0) {
            this->selectionIdx += LEVEL_SELECT_ROW_SIZE-1;
        } else {
            this->selectionIdx -= 1;
        }
        break;

    case SDLK_RIGHT:
    case SDLK_6:
        if (this->selectionIdx % LEVEL_SELECT_ROW_SIZE == LEVEL_SELECT_ROW_SIZE-1) {
            this->selectionIdx -= LEVEL_SELECT_ROW_SIZE-1;
        } else {
            this->selectionIdx += 1;
        }
        break;

    case SDLK_RETURN:
        // Check for invalid level
        try {
            return std::make_unique<LevelMenu>(this->selectionIdx + 1);
        } catch(const std::invalid_argument& e) {
            this->invalidSelectionTime = 1000;
        }
        break;
        
    default:
        break;
    }

    return nullptr;
}

std::unique_ptr<Menu> LevelSelectMenu::update(Uint32 delta_time) {
    if (delta_time > this->invalidSelectionTime) {
        this->invalidSelectionTime = 0;
    } else {
        this->invalidSelectionTime -= delta_time;
    }

    return nullptr;
}

void LevelSelectMenu::draw(SDL_Surface* screen) {
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 28, 43, 58));
    
    // Level buttons
    SDL_Surface* button_tex = ImageManager::getTexture(image_button);
    SDL_Surface* button_selected_tex = ImageManager::getTexture(image_button_selected);
    for (int i = 0; i < LEVEL_NUMS; i++) {
        SDL_Surface* tex = i == this->selectionIdx ? button_selected_tex : button_tex;
        int posX = 36 + (i%LEVEL_SELECT_ROW_SIZE)*(tex->w+4);
        int posY = 48 + (i/LEVEL_SELECT_ROW_SIZE)*(tex->h+6);

        ImageManager::drawTexture(tex, screen, posX, posY);
        FontManager::drawText(screen, this->font, (posX + tex->w/2) - int(3* (i+1 > 9 ? 2.5 : 1)), (posY + tex->h/2) - 4, "%d", i+1);
    }

    // Text above
    FontManager::drawText(screen, this->font, 105, 15, "Select a level");
    if (this->invalidSelectionTime > 0) {
        FontManager::drawText(screen, this->font, 45, 31, "That level does not exist yet");
    }

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
