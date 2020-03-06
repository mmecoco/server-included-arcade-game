#include "Room.hpp"

void Room::AddPlayer(std::string id, std::string host, unsigned short port, connection_ptr conn)
{
    std::pair<std::string, unsigned short> target;

    target = std::make_pair(host, port);
    datas_[id] = target;
    connection_list_.push_back(conn);
}

void Room::Reset()
{
    datas_.clear();
}

void Room::DeletePlayer(std::string name)
{
    datas_.erase(name);
}

unsigned int Room::GetPlayerNum() const
{
    return datas_.size();
}