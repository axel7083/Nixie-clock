# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("Clock2.0" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/Clock.cpp include/Clock.h src/managers/WifiManager.cpp include/managers/WifiManager.h src/managers/BackLightsManager.cpp include/managers/BackLightsManager.h src/managers/BLEManager.cpp include/managers/BLEManager.h src/managers/TimeManager.cpp include/managers/TimeManager.h src/managers/FilesManager.cpp include/managers/FilesManager.h src/managers/ButtonsManager.cpp include/managers/ButtonsManager.h include/bluetooth/BluetoothService.h include/bluetooth/BacklightsService.h src/managers/ScreensManager.cpp include/managers/ScreensManager.h src/hardware/ChipSelect.cpp include/hardware/ChipSelect.h include/hardware/Hardware.h include/managers/Manager.h src/utils/Storage.cpp include/utils/Storage.h src/models/Button.cpp include/models/Button.h src/hardware/TFTs.cpp include/hardware/TFTs.h)
