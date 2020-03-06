cmake_minimum_required (VERSION 3.10)
project (Eligos)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-g")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=lib++")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include_directories(
  Application
  Application/Network
  RendererEngine
  RendererEngine/SFML
)

conan_basic_setup() 

find_package (Threads REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set (RENDER_ENGINE
        RendererEngine/SFML/Font.cpp
        RendererEngine/SFML/SfmlRenderer.cpp
        RendererEngine/SFML/Sprite.cpp
        RendererEngine/SFML/Text.cpp
        RendererEngine/SFML/Texture.cpp
)

set (APPLICATION
        Application/Application.cpp
        Application/Layer.cpp
        Application/Scene.cpp
)

set (ENTITY_COMPONENT_SYS
        Application/EntityComponentSystem/SystemBase.cpp
        Application/EntityComponentSystem/Entities.cpp
        Application/EntityComponentSystem/ComponentHolder.cpp
        Application/EntityComponentSystem/SystemFactory.cpp
        Application/EntityComponentSystem/ComponentFactory.cpp
        Application/EntityComponentSystem/EntitiesFactory.cpp
        Application/EntityComponentSystem/EventManager.cpp
)

set (DERIVATE_COMPONENT
        Application/EntityComponentSystem/DerivateComponent/PositionComponent.hpp
       Application/EntityComponentSystem/DerivateComponent/DirectionComponent.hpp
        Application/EntityComponentSystem/DerivateComponent/VelocityComponent.hpp
        Application/EntityComponentSystem/DerivateComponent/DrawableComponent.hpp
        Application/EntityComponentSystem/DerivateComponent/FontComponent.hpp
	Application/EntityComponentSystem/DerivateComponent/PlayableComponent.hpp
        Application/EntityComponentSystem/DerivateComponent/InputComponent.hpp
)

set (DERIVATE_SYSTEM
        Application/EntityComponentSystem/DerivateSystem/GraphicPositionSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/moveSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/RenderSystem.cpp
	Application/EntityComponentSystem/DerivateSystem/SendSystem.cpp
	Application/EntityComponentSystem/DerivateSystem/ReceiveSystem.cpp
	Application/EntityComponentSystem/DerivateSystem/attributeInputSystem.cpp
	Application/EntityComponentSystem/DerivateSystem/changeSpeedSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/PopMissileSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/ColideSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/DamageSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/deathSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/BonusSystem.cpp
        Application/EntityComponentSystem/DerivateSystem/EndGameSystem.cpp
)

set (SCRIPT_ENGINE
        ScriptEngine/Script.cpp
        ScriptEngine/ModifyValueScript.cpp
)

set (TCP_SERVER_SRC
  Application/Network/Room/Room.cpp
  Application/Network/tcp_server/tcp_server.cpp
  Application/Network/Fork.cpp
  Application/Network/udp_server/udp_server.cpp
)

set (TCP_CLIENT_SRC
  Application/Network/tcp_client/tcp_client.cpp
  Application/Network/udp_client/udp_client.cpp
)

set (SERVER_MAIN
  main/main_server.cpp
  #mainApp.cpp
)

set (CLIENT_MAIN
  main/main_client.cpp
  #mainApp.cpp
)

set(LD_FLAGS_LIB
  # -lsfml-audio
)

if (UNIX)

elseif (WIN32)

endif (UNIX)


add_executable(server ${LD_FLAGS} ${SERVER_MAIN} ${APPLICATION} ${ENTITY_COMPONENT_SYS} ${DERIVATE_COMPONENT} ${DERIVATE_SYSTEM} ${SCRIPT_ENGINE} ${RENDER_ENGINE} ${TCP_SERVER_SRC})
target_link_libraries (server ${CONAN_LIBS} ${LD_FLAGS} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} boost_system boost_serialization pthread)

add_executable(client ${LD_FLAGS} ${CLIENT_MAIN} ${APPLICATION} ${ENTITY_COMPONENT_SYS} ${DERIVATE_COMPONENT} ${DERIVATE_SYSTEM} ${SCRIPT_ENGINE} ${RENDER_ENGINE} ${TCP_CLIENT_SRC})
target_link_libraries (client ${CONAN_LIBS} ${LD_FLAGS} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} boost_system boost_serialization pthread)

set ( LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(server PUBLIC
        Application        
        Application/EntityComponentSystem        
        Application/EntityComponentSystem/DerivateSystem
        Application/EntityComponentSystem/DerivateComponent
        ScriptEngine
        RendererEngine
        RendererEngine/SFML
)

target_include_directories(client PUBLIC
        Application        
        Application/EntityComponentSystem        
        Application/EntityComponentSystem/DerivateSystem
        Application/EntityComponentSystem/DerivateComponent
        ScriptEngine
        RendererEngine
        RendererEngine/SFML
)
