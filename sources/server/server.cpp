#include "server.hpp"

SINGLETON_DEFINITOR(serv, Server)

serv::Server::Server() noexcept : core::Module("server")
{
}
bool
serv::Server::loopBody() noexcept
{
    if(!running){
        CROW_ROUTE(app, "/")([]() {
            return "Hello, world!";
        });

         CROW_ROUTE(app, "/json")([]() {
            crow::json::wvalue response;
            response["message"] = "Hello JSON!";
            response["status"] = 200;
            return response;
        });

        std::thread([this]() {
            app.port(18080).multithreaded().run();
        }).detach();

        running = true;
        std::cout << "Запущено бля здесь http://localhost:18080\n";
    }

    util::Yield::small();

    return true; 
    
}
void
serv::Server::commandSetup() const noexcept
{
   
   
}
void
serv::Server::variableSetup() const noexcept
{
    
}
