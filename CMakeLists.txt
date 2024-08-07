cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Set to use solution folders for organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (WIN32)
    add_compile_definitions(QE_PLATFORM_WINDOWS)
ENDIF()

add_compile_definitions(QE_ROOT_DIR=${CMAKE_SOURCE_DIR})


# Set project
project(QuestEngine CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DTRACY_ENABLE=1)
add_compile_options(-MP -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-pragma-once-outside-header)
add_compile_options(-ftime-trace -c)


# Set QUEST_ROOT from environment var
set(QUEST_ROOT ${CMAKE_SOURCE_DIR})

#--- VENDOR SUBDIRECTORIES ---#
message("Building glfw...")
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${QUEST_ROOT}/ThirdParty/Engine/glfw)
message("Done building glfw")

# Engine directory
add_subdirectory(${QUEST_ROOT}/QuestEngine)

# Editor directory
#add_subdirectory(%{QUEST_ROOT}/Quest-Editor)

# Sandbox directory
add_subdirectory(${QUEST_ROOT}/Sandbox)

# Vulkan Renderer subdirectory
#add_subdirectory(${QUEST_ROOT}/VulkanRenderer)

# Set startup project to Sandbox
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)