#ifndef _INCLUDE_SERVER
#define _INCLUDE_SERVER

#include <boost/beast.hpp>
#include <filesystem>
#include <string>
#include <thread>

#include "util.h"
#include <memory>
#include <thread>

auto run(const boost::asio::ip::address address, const unsigned short port,
         std::shared_ptr<std::string> doc_root) -> void;
auto handle_session(boost::asio::ip::tcp::socket &socket,
                    std::shared_ptr<std::string const> const &doc_root) -> void;
#endif