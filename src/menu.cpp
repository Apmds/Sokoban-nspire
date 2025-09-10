#include "menu.hpp"
#include "image_manager.hpp"
#include "image_data.hpp"
#include "level_data.hpp"
#include <stdexcept>

#define LEVEL_COMPLETE_DELAY 1000 // milliseconds needed to wait after completing a level
#define LEVEL_SELECT_ROW_SIZE 6
#define LEVEL_NUMS 24
#define MAIN_MENU_ANIMATION_TIME 300 // milliseconds that a frame of the main menu animation lasts

MainMenu::MainMenu() {
    this->font = FontManager::loadFont(image_font, 7, 9, 225, 114, 91);
    this->close = SDL_FALSE;
    this->animationTimer = 0;
}

MainMenu::~MainMenu() {
    FontManager::unloadFont(this->font);
}

std::unique_ptr<Menu> MainMenu::input(SDLKey sym) {
    switch (sym) {
    case SDLK_RETURN:
        return std::make_unique<LevelSelectMenu>();
    case SDLK_ESCAPE:
        this->close = SDL_TRUE;
        break;
    default:
        break;
    }

    return nullptr;
}

std::unique_ptr<Menu> MainMenu::update(Uint32 delta_time) {
    animationTimer += delta_time;
    if (animationTimer > 30*MAIN_MENU_ANIMATION_TIME) {
        animationTimer = 0;
    }
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
    switch (animationTimer / MAIN_MENU_ANIMATION_TIME) {
    case 0:
        ImageManager::drawTile(player_tex, screen, 8*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 1:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 2:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 3:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 4:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 5:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 6:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 7:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 8:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 9:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 11*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 10:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 11*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 11:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 11*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 12:
        ImageManager::drawTile(player_tex, screen, 11*TILE_WIDTH, 11*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 13:
        ImageManager::drawTile(player_tex, screen, 11*TILE_WIDTH, 11*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 14:
        ImageManager::drawTile(player_tex, screen, 11*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 15:
        ImageManager::drawTile(player_tex, screen, 11*TILE_WIDTH, 12*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 16:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 17:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 18:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 19:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 20:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;

    case 21:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 22:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_RIGHT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 23:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 12*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 24:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 11*TILE_HEIGHT, DIR_UP);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 25:
        ImageManager::drawTile(player_tex, screen, 10*TILE_WIDTH, 11*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 26:
        ImageManager::drawTile(player_tex, screen, 9*TILE_WIDTH, 11*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 27:
        ImageManager::drawTile(player_tex, screen, 8*TILE_WIDTH, 11*TILE_HEIGHT, DIR_LEFT);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 28:
        ImageManager::drawTile(player_tex, screen, 8*TILE_WIDTH, 11*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;
    case 29:
        ImageManager::drawTile(player_tex, screen, 8*TILE_WIDTH, 12*TILE_HEIGHT, DIR_DOWN);
        ImageManager::drawTile(box_tex, screen, 9*TILE_WIDTH, 12*TILE_HEIGHT, 0);
        break;

    default:
        break;
    }
    

    
    SDL_Flip(screen);
}

SDL_bool MainMenu::shouldClose() {
    return this->close;
}

LevelSelectMenu::LevelSelectMenu() : LevelSelectMenu(0) {}

LevelSelectMenu::LevelSelectMenu(int selectionIdx) {
    this->font = FontManager::loadFont(image_font, 7, 9, 225, 114, 91);
    this->selectionIdx = selectionIdx;
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

    case SDLK_ESCAPE:
        return std::make_unique<MainMenu>();
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
        int posX = 43 + (i%LEVEL_SELECT_ROW_SIZE)*(tex->w+18);
        int posY = 64 + (i/LEVEL_SELECT_ROW_SIZE)*(tex->h+18);

        ImageManager::drawTexture(tex, screen, posX, posY);
        FontManager::drawTextCentered(screen, this->font, (posX + tex->w/2), (posY + tex->h/2), "%d", i+1);
    }

    // Text above
    FontManager::drawText(screen, this->font, 105, 15, "Select a level");
    if (this->invalidSelectionTime > 0) {
        FontManager::drawText(screen, this->font, 45, 31, "That level does not exist yet");
    }

    SDL_Flip(screen);
}

SDL_bool LevelSelectMenu::shouldClose() {
    return SDL_FALSE;
}

// Gay function bc Level does not have a default constructor
static Level loadLevel(int level_num) {
    switch (level_num) {
	    case 1:
	    	return Level(level1size.x, level1size.y, level1map, level1playerPos, level1boxes, level1storages);
	    case 2:
	    	return Level(level2size.x, level2size.y, level2map, level2playerPos, level2boxes, level2storages);
        case 3:
	    	return Level(level3size.x, level3size.y, level3map, level3playerPos, level3boxes, level3storages);
        case 4:
	    	return Level(level4size.x, level4size.y, level4map, level4playerPos, level4boxes, level4storages);
        case 5:
	    	return Level(level5size.x, level5size.y, level5map, level5playerPos, level5boxes, level5storages);
        case 6:
	    	return Level(level6size.x, level6size.y, level6map, level6playerPos, level6boxes, level6storages);
        case 7:
	    	return Level(level7size.x, level7size.y, level7map, level7playerPos, level7boxes, level7storages);
        case 8:
	    	return Level(level8size.x, level8size.y, level8map, level8playerPos, level8boxes, level8storages);
        case 9:
	    	return Level(level9size.x, level9size.y, level9map, level9playerPos, level9boxes, level9storages);
        case 10:
	    	return Level(level10size.x, level10size.y, level10map, level10playerPos, level10boxes, level10storages);
        case 11:
	    	return Level(level11size.x, level11size.y, level11map, level11playerPos, level11boxes, level11storages);
        case 12:
	    	return Level(level12size.x, level12size.y, level12map, level12playerPos, level12boxes, level12storages);
	    default:
	    	throw std::invalid_argument("Unknown level number.");
	}
}

LevelMenu::LevelMenu(int level_num) : level(loadLevel(level_num)) {
    this->level_num = level_num;
    this->complete_delay = LEVEL_COMPLETE_DELAY;
    this->ui_font = FontManager::loadFont(image_font, 7, 9, 225, 114, 91);
    this->completed_font = FontManager::loadFont(image_font, 7, 9, 66, 245, 105);
}

LevelMenu::~LevelMenu() {
    FontManager::unloadFont(this->ui_font);
    FontManager::unloadFont(this->completed_font);
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
    
    case SDLK_0:
        this->level.rewind();
        break;
    
    case SDLK_ESCAPE:
        return std::make_unique<LevelSelectMenu>(this->level_num-1);
        
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
    FontManager::drawText(screen, this->ui_font, 10, 10, "Steps: %d", this->level.getSteps());

    if (this->level.isCompleted()) {
        FontManager::drawTextCentered(screen, this->completed_font, 160, 120, "\x1 \x1 Yay, the level is completed! \x1 \x1");
    }
    
    SDL_Flip(screen);
}

SDL_bool LevelMenu::shouldClose() {
    return SDL_FALSE;
}