#include "Fork.hpp"
#include "UdpServer.hpp"

Fork::Fork(std::vector<stock> info, std::string ip, unsigned short port)
{
  pid_t pid = fork();
  if (pid == 0)
    {
      udp_ = new Server(info, ip, port);

      udp_->run();
      std::cout << "Dont go to sleep\n";
      kill(getpid(), SIGKILL);
    }
    else
      std::cout << "Child's id = " << pid << std::endl;
  return;
};
