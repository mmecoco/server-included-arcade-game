#pragma once

#include <iostream>
#include "Application.hpp"
#include "SystemFactory.hpp"
#include "ComponentFactory.hpp"
#include "EntitiesFactory.hpp"
#include "DrawableComponent.hpp"
#include "Script.hpp"
#include "RenderSystem.hpp"
#include "attributeInputSystem.hpp"
#include "changeSpeedSystem.hpp"
#include "stock.hpp"
#include "SendSystem.hpp"
#include "ReceiveSystem.hpp"

class Client : public Eligos::Application
{
public:
  Client(std::vector<stock> data, std::string id)
  {
		m_api.reset(new Eligos::SfmlRenderer());
		m_api->CreateWindow();
		m_loadedScriptname.push_back({DEFAULT_BCK});
		m_loadedScriptname.push_back({DEFAULT_GAME});
		m_loadedScriptname.push_back({DEFAULT_UI_HEALTH});
		m_loadedScriptname[2].push_back(DEFAULT_UI_SHIELD);
		m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EnemiesEntity.json");
		m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EventScript.json");
		m_loadedScriptname[1].push_back("../ScriptFile/Scene0/EventScript1.json");
		m_loadedScriptname[1].push_back("../ScriptFile/Scene0/missile1Entity.json");
		m_loadedScriptname[0].push_back("../ScriptFile/Scene1/StageEntity.json");
		m_loadedScriptname[0].push_back("../ScriptFile/Scene1/EventScript2.json");

		try
		{
			generateScene();
			RenderSystem *sys = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
			RenderSystem *sys1 = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
			RenderSystem *sys2 = (RenderSystem *)SystemFactory::Get()->CreateSystem("RENDERER");
			sys->init(m_api);
			sys1->init(m_api);
			sys2->init(m_api);
			m_SceneStack[0]->addSystemLayer(sys, 0);
			m_SceneStack[0]->addSystemLayer(sys1, 1);
			m_SceneStack[0]->addSystemLayer(sys2, 2);

			SystemBase *graphPos = SystemFactory::Get()->CreateSystem("RENDERERPOS");
			SystemBase *graphPos1 = SystemFactory::Get()->CreateSystem("RENDERERPOS");
			SystemBase *graphPos2 = SystemFactory::Get()->CreateSystem("RENDERERPOS");

			m_SceneStack[0]->addSystemLayer(graphPos, 0);
			m_SceneStack[0]->addSystemLayer(graphPos1, 1);
			m_SceneStack[0]->addSystemLayer(graphPos2, 2);

			SendSystem *sender_server = (SendSystem *)SystemFactory::Get()->CreateSystem("SEND");
			boost::asio::io_service io;
			int i = 0;
			while (id != data[i].id)
			  i++;
			std::cout << "Creating sender from " << data[i].ip << ":" << data[i].port << std::endl;
			boost::asio::ip::udp::socket *target_socket = new boost::asio::ip::udp::socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(data[i].ip.c_str()), data[i].port));
			boost::asio::ip::udp::endpoint target_endpoint(boost::asio::ip::address::from_string(data[0].ip.c_str()), data[0].port);
			std::cout << "Send client ready to initialized\n";
			sender_server->init(target_socket, target_endpoint);

			m_SceneStack[0]->addSystemLayer(sender_server, 1);

			ReceiveSystem *receiver_server = (ReceiveSystem *)SystemFactory::Get()->CreateSystem("RECEIVE");
			receiver_server->init(target_socket, target_endpoint);
			m_SceneStack[0]->addSystemLayer(receiver_server, 1);
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
			throw std::logic_error("Invalid Game configuration");
    	}
	}
  virtual ~Client() = default;
};
