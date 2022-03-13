#include "pch.h"
#include "settings.h"

namespace RedWood
{
	Settings* Settings::instance = nullptr;

	Settings::Settings()
	{
		SetupProperties();

		const std::string initFilePath = this->optionsINIDir + this->optionsINIFileName;
		if(!bfs::exists(initFilePath))
		{
			auto justToCreateFile = bfs::ofstream(initFilePath);
		}

		bpt::read_ini(initFilePath, this->pt);

		this->loadRendererType();
		this->loadScreenSize();
	}

	Settings::~Settings()
	{
		delete instance;
	}

	Settings* Settings::getInstance()
	{
		if(instance == nullptr)
		{
			instance = new Settings();
		}

		return instance;
	}

	void Settings::SetupProperties()
	{
		this->CurrentRendererType.getter = [this]()
		{
			return this->rendererType;
		};

		this->ScreenSize.getter = [this]()
		{
			return this->screenSize;
		};
		this->ScreenSize.setter = [this](const vec2& other)
		{
			return this->screenSize = other;
		};

		this->CurrentWindowMode.getter = [this]()
		{
			return this->windowMode;
		};
		this->CurrentWindowMode.setter = [this](WindowMode other)
		{
			return this->windowMode = other;
		};
	}

	void Settings::loadRendererType()
	{
		boost::optional<int> typeInt = this->pt.get_optional<int>("General.RendererType");
		this->rendererType = typeInt.has_value() ? static_cast<RendererType>(typeInt.value()) : RendererType::eDefault;
	}

	void Settings::loadScreenSize()
	{
		boost::optional<int> width = this->pt.get_optional<int>("General.ScreenWidth");
		boost::optional<int> height = this->pt.get_optional<int>("General.ScreenHeight");

		const vec2 size =
		{
			width.has_value() ? width.value() : 1600,
			height.has_value() ? height.value() : 900
		};

		this->screenSize = size;
	}
}
