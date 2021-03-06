cmake_minimum_required (VERSION 3.0)

project (halley-test-rig)

set(HALLEY_PROJECT_EMBED 1)
#set(HALLEY_PATH "" CACHE FILEPATH "Path to the Halley root")
set(HALLEY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/halley)
set(HOTRELOAD 0 CACHE BOOL "Sets whether to hot-reload this project")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HALLEY_PATH}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#set(IOS_BUNDLE_IDENTIFIER "com.bearwaves.halley-test-rig")
set(IOS_VERSION "1.0.0")
set(IOS_BUILD_NUMBER "1")
set(IOS_NAME "Halley Test Rig")

include(HalleyProject)


if(NOT (DEFINED HALLEYPROJ_BIN_DIR))
	set(HALLEYPROJ_BIN_DIR "bin")
endif()

set (SOURCES
	"src/core/test_rig.cpp"
	"src/stages/game_stage.cpp"
	"halley/gen/cpp/registry.cpp"
	)

set (HEADERS
	"src/core/test_rig.h"
	"src/stages/game_stage.h"
	)

set (GEN_DEFINITIONS
	)

halleyProject(halley-test-rig "${SOURCES}" "${HEADERS}" "${GEN_DEFINITIONS}" ${CMAKE_CURRENT_SOURCE_DIR}/${HALLEYPROJ_BIN_DIR})
