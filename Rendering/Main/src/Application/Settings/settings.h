#ifndef SETTINGS_H
#define SETTINGS_H

#include "../../Rendering/General/Window/windowMode.h"

namespace RedWood
{
	class Settings final
	{
	private:
		Settings();

	public:
		Settings(const Settings&) = delete;
		Settings(Settings&&) = delete;
		~Settings();

		Settings& operator=(const Settings&) = delete;
		Settings& operator=(Settings&&) = delete;

		static Settings* getInstance();

		Property<RendererType, true, false> CurrentRendererType;
		Property<vec2> ScreenSize;
		Property<WindowMode> CurrentWindowMode;
	private:
		void SetupProperties();

		static Settings* instance;

		const std::string optionsINIDir;
		const std::string optionsINIFileName = "opt.ini";
		bpt::ptree pt;

		void loadRendererType();
		RendererType rendererType;

		void loadScreenSize();
		vec2 screenSize;

		void loadWindowMode();
		WindowMode windowMode;
	};
}
#endif