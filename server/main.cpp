#include "Listener.h"

int main(int argc, char* argv[])
{
    const auto port = 8001;
    const auto threads = 1;

    auto ep = tcp::endpoint(tcp::v4(), port);
    net::io_context ioc{threads};

    std::make_shared<Listener>(ioc, ep)->run();

    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    return EXIT_SUCCESS;
}
