#include "FailHandler.h"
#include<iostream>

void FailHandler::fail(beast::error_code ec, char const* what){
    std::cerr << what << ": " << ec.message() << "\n";
}
