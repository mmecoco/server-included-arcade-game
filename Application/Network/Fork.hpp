#include <ctime>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include "Server.hpp"

class Fork
{
public:
  Fork(std::vector<stock> info, std::string ip, unsigned short port);
  ~Fork(){};
  void setMyPid(pid_t x) {m_pid = getpid();};
  pid_t getMyPid() const {return m_pid;};
private:
  pid_t m_pid;
  Server *udp_;
};
