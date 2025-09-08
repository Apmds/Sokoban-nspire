#ifndef MENU_HPP
#define MENU_HPP

#include "level.hpp"
#include "font_manager.hpp"
#include <SDL/SDL.h>
#include <memory>

class Menu {
	public:
        // Runs when an input event is caught
		virtual std::unique_ptr<Menu> input(SDLKey sym) = 0;
		
        // Runs every frame. delta time is the ms since last frame
        virtual std::unique_ptr<Menu> update(Uint32 delta_time) = 0;
		
        // Draws the menu to the screen
        virtual void draw(SDL_Surface* screen) = 0;

        // Whether or not the menu wants the game to close
        virtual SDL_bool shouldClose() = 0;

        virtual ~Menu() = default;
};

class MainMenu : public Menu {
    private:
        FontManager::Font* font;
        SDL_bool close;
        Uint32 animationTimer;
	public:
        MainMenu();
        ~MainMenu();

        std::unique_ptr<Menu> input(SDLKey sym);
		std::unique_ptr<Menu> update(Uint32 delta_time);
		void draw(SDL_Surface* screen);
        SDL_bool shouldClose();
};

class LevelSelectMenu : public Menu {
    private:
        int selectionIdx;
        Uint32 invalidSelectionTime;
        FontManager::Font* font;
	public:
        LevelSelectMenu();
        ~LevelSelectMenu();

        std::unique_ptr<Menu> input(SDLKey sym);
        std::unique_ptr<Menu> update(Uint32 delta_time);
		void draw(SDL_Surface* screen);
        SDL_bool shouldClose();
};

class LevelMenu : public Menu {
    private:
        Level level;
        Uint32 complete_delay; // Time(ms) to transition off this screen after completition
        FontManager::Font* font;
	public:
        LevelMenu(int level_num);
        ~LevelMenu();

        std::unique_ptr<Menu> input(SDLKey sym);
		std::unique_ptr<Menu> update(Uint32 delta_time);
		void draw(SDL_Surface* screen);
        SDL_bool shouldClose();
};

#endif