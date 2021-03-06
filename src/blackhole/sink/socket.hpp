#pragma once

#include "socket/udp.hpp"
#include "socket/tcp.hpp"

#include "blackhole/repository/factory/traits.hpp"

namespace blackhole {

namespace sink {

namespace socket {

struct config_t {
    std::string host;
    std::uint16_t port;
};

} // namespace socket

template<typename Protocol, typename Backend = socket::boost_backend_t<Protocol> >
class socket_t {
    Backend m_backend;

public:
    typedef socket::config_t config_type;

    static const char* name() {
        return Backend::name();
    }

    socket_t(const config_type& config) :
        m_backend(config.host, config.port)
    {}

    socket_t(const std::string& host, std::uint16_t port) :
        m_backend(host, port)
    {}

    void consume(const std::string& message) {
        m_backend.write(message);
    }

    Backend& backend() {
        return m_backend;
    }
};

} // namespace sink

template<typename Protocol>
struct factory_traits<sink::socket_t<Protocol>> {
    typedef sink::socket_t<Protocol> sink_type;
    typedef typename sink_type::config_type config_type;

    static void map_config(const aux::extractor<sink_type>& ex, config_type& config) {
        ex["host"].to(config.host);
        ex["port"].to(config.port);
    }
};

} // namespace blackhole
