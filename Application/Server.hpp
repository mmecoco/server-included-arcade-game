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

class Server : public Eligos::Application
{
public:
  Server(std::vector<stock> contact_list, std::string ip, unsigned short port)
  {
    m_api.reset(new Eligos::SfmlRenderer());
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

	try {
		generateScene();

		SystemBase *movesys = SystemFactory::Get()->CreateSystem("MOVE");
		m_SceneStack[0]->addSystemLayer(movesys, 1);
		attributeInputSystem *attSys = (attributeInputSystem *)SystemFactory::Get()->CreateSystem("ATTRIBUTE");
		attSys->init(m_api);
		m_SceneStack[0]->addSystemLayer(attSys, 1);
		SystemBase *speed = SystemFactory::Get()->CreateSystem("SPEEDCHANGE");
		m_SceneStack[0]->addSystemLayer(speed, 1);
		SystemBase *shoot = SystemFactory::Get()->CreateSystem("SHOOT");
		m_SceneStack[0]->addSystemLayer(shoot, 1);
		SystemBase *colide = SystemFactory::Get()->CreateSystem("COLIDE");
		m_SceneStack[0]->addSystemLayer(colide, 1);
		SystemBase *damage = SystemFactory::Get()->CreateSystem("DAMAGE");
		m_SceneStack[0]->addSystemLayer(damage, 1);
		SystemBase *bonus = SystemFactory::Get()->CreateSystem("BONUS");
		m_SceneStack[0]->addSystemLayer(bonus, 1);
		SystemBase *EndGame = SystemFactory::Get()->CreateSystem("ENDGAME");
		m_SceneStack[0]->addSystemLayer(EndGame, 1);
		SystemBase *death = SystemFactory::Get()->CreateSystem("DEATH");
		m_SceneStack[0]->addSystemLayer(death, 1);

		SendSystem *sender_server = (SendSystem *)SystemFactory::Get()->CreateSystem("SEND");
		boost::asio::io_service io;
		std::vector<boost::asio::ip::udp::endpoint> endpoint_vector;
		for (auto it = contact_list.begin(); it != contact_list.end(); it++) {
			boost::asio::ip::udp::endpoint target_endpoint (boost::asio::ip::address::from_string(it->ip.c_str()), it->port);
			endpoint_vector.push_back(target_endpoint);
		}
		std::cout << "endpoint vector size = " << endpoint_vector.size() << std::endl;
		boost::asio::ip::udp::socket *target_sock = new boost::asio::ip::udp::socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip.c_str()), port));

		sender_server->init(target_sock, endpoint_vector);
		m_SceneStack[0]->addSystemLayer(sender_server, 0);

		ReceiveSystem *receiver_server = (ReceiveSystem *)SystemFactory::Get()->CreateSystem("RECEIVE");
		receiver_server->init(target_sock, endpoint_vector);
		m_SceneStack[0]->addSystemLayer(receiver_server, 0);
    }
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		throw std::logic_error("Invalid Game configuration");
	}
  };
  virtual ~Server() = default;
};
