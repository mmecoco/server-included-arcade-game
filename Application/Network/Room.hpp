#pragma once

#include <map>
#include <string>
#include <vector>
#include "connection.hpp"

class Room
{
    public:
        Room(std::string id, unsigned int num_player) : id_(id), num_player_(num_player) {};
        ~Room() {};
        void AddPlayer(std::string id, std::string host, unsigned short port, connection_ptr conn);
        void Reset();
        void DeletePlayer(std::string name);
        unsigned int GetPlayerNum() const;
        unsigned int GetMaxPlayerNum() const {return num_player_;};
        std::string GetId() const {return id_;};
        std::map<std::string, std::pair<std::string, unsigned short>> GetDatas() const {return datas_;};
        std::vector<connection_ptr> GetConnection() const {return connection_list_;};
    private:
        std::string id_;
        unsigned int num_player_;
        std::map<std::string, std::pair<std::string, unsigned short>> datas_; // player_id : (host, port)

        std::vector<connection_ptr> connection_list_;
};