#include "starter.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: FileServer <address> <port> <doc_root>\n"
              << "Example:\n"
              << "> FileServer 0.0.0 8080 .\n";
    return EXIT_FAILURE;
  }
  try {
    auto const address = boost::beast::net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    run(address, port, doc_root);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}