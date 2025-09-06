#ifndef MENU_HPP
#define MENU_HPP

#include "level.hpp"
#include "font_manager.hpp"
#include <SDL/SDL.h>
#include <memory>

class Menu {
	public:
		virtual std::unique_ptr<Menu> input(SDLKey sym) = 0;
		virtual std::unique_ptr<Menu> update(Uint32 delta_time) = 0;
		virtual void draw(SDL_Surface* screen) = 0;

        virtual ~Menu() = default;
};

class MainMenu : public Menu {
    private:
        FontManager::Font* font;
	public:
        MainMenu();
        ~MainMenu();

        std::unique_ptr<Menu> input(SDLKey sym);
		std::unique_ptr<Menu> update(Uint32 delta_time);
		void draw(SDL_Surface* screen);
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
};

class LevelMenu : public Menu {
    private:
        Level level;
        Uint32 complete_delay; // Time(ms) to transition off this screen after completition
        nSDL_Font* font;
	public:
        LevelMenu(int level_num);
        ~LevelMenu();

        std::unique_ptr<Menu> input(SDLKey sym);
		std::unique_ptr<Menu> update(Uint32 delta_time);
		void draw(SDL_Surface* screen);
};

#endif