#ifndef PCH_H
#define PCH_H

// C++ std
#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <fstream>
#include <array>
#include <queue>

// C++ boost
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace bpt = boost::property_tree;

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

//dependencies
#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc//type_ptr.hpp"

//this project
#include "../Utilities/types.h"
#include "../Utilities/property.h"
#include "../Utilities/APIFactory.h"

#include "../EventSystem/General/Keyboard/keyboardKeyAction.h"
#include "../EventSystem/General/Keyboard/keyboardKey.h"
#include "../EventSystem/General/Keyboard/keyboard.h"
#include "../EventSystem/GLFW/Keyboard/keyboardKeyGLFW.h"
#include "../EventSystem/GLFW/Keyboard/keyboardKeyActionGLFW.h"

#include "../EventSystem/General/Mouse/mouseButtonAction.h"
#include "../EventSystem/General/Mouse/mouseButton.h"
#include "../EventSystem/General/Mouse/mouse.h"
#include "../EventSystem/GLFW/Mouse/mouseButtonGLFW.h"
#include "../EventSystem/GLFW/Mouse/mouseButtonActionGLFW.h"

#include "../Rendering/General/Renderer/rendererType.h"
#include "../Application/Settings/settings.h"

#endif
