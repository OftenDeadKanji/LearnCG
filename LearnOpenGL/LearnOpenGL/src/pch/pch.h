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
#include <unordered_map>

// C++ boost
#include <boost/filesystem.hpp>

// dependencies
#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "stb_image.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// this project
#include "../Utilities/types.h"
#include "../ResourceManager/resourceManager.h"

#include "../EventSystem/Keyboard/keyboardKeyAction.h"
#include "../EventSystem/Keyboard/keyboardKey.h"
#include "../EventSystem/Keyboard/keyboard.h"

#include "../EventSystem/Mouse/mouseButtonAction.h"
#include "../EventSystem/Mouse/mouseButton.h"
#include "../EventSystem/Mouse/mouse.h"

#endif
