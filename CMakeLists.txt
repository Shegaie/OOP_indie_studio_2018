cmake_minimum_required(VERSION 3.11)
project(bomberman)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)

find_package(Irrlicht REQUIRED)
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

include_directories(${Irrlicht_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIR}
        src
        include
        )

add_executable(bomberman
        src/AI/AI.cpp
        src/AI/AI.hpp
        src/Bomberman/Bomberman.cpp
        src/Bomberman/Bomberman.hpp
        src/BombermanException/BombermanException.cpp
        src/BombermanException/BombermanException.hpp
        src/Button/Button.cpp
        src/Button/Button.hpp
        src/Effect/Explosion.cpp
        src/Effect/Explosion.hpp
        src/Effect/MagicCandle.cpp
        src/Effect/MagicCandle.hpp
        src/EventManager/EventManager.cpp
        src/EventManager/EventManager.hpp
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Map/Map.cpp
        src/Map/Map.hpp
        src/Menu/MenuHome/MenuHome.cpp
        src/Menu/MenuHome/MenuHome.hpp
        src/Menu/MenuHowToPlay/MenuHowToPlay.cpp
        src/Menu/MenuHowToPlay/MenuHowToPlay.hpp
        src/Menu/MenuLoad/MenuLoad.cpp
        src/Menu/MenuLoad/MenuLoad.hpp
        src/Menu/MenuNew/MenuNew.cpp
        src/Menu/MenuNew/MenuNew.hpp
        src/Menu/MenuSettings/MenuSettings.cpp
        src/Menu/MenuSettings/MenuSettings.hpp
        src/Menu/IMenu.hpp
        src/Menu/Menu.cpp
        src/Menu/Menu.hpp
        src/Player/Player.cpp
        src/Player/Player.hpp
        src/PowerUp/BombPowerUp.cpp
        src/PowerUp/BombPowerUp.hpp
        src/PowerUp/IPowerUp.hpp
        src/PowerUp/RangePowerUp.cpp
        src/PowerUp/RangePowerUp.hpp
        src/PowerUp/SpeedPowerUp.cpp
        src/PowerUp/SpeedPowerUp.hpp
        src/PowerUp/WallPassPowerUp.cpp
        src/PowerUp/WallPassPowerUp.hpp
        src/SoundManager/SoundManager.cpp
        src/SoundManager/SoundManager.hpp
        src/Sprite2D/Sprite2D.cpp
        src/Sprite2D/Sprite2D.hpp
        src/Timer/Timer.cpp
        src/Timer/Timer.hpp
        src/Bomb/Bomb.cpp
        src/Bomb/Bomb.hpp
        src/IScene.hpp
        src/main.cpp)

target_link_libraries(bomberman ${Irrlicht_LIBRARIES} ${SFML_LIBRARIES})
