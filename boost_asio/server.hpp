#pragma once

class echo_server: boost::noncopyable
{
public:
    echo_server(io_service &);
    void start_accept();
    void stop_accept();
private:
    struct connection
    {
        boost::shared_ptr<sock> sock_ptr;
        char                    buf[BUF_SIZE + 1];
        connection() = default;
        connection(io_service &service) : 
            sock_ptr(new sock(service))
        {}
    };
    void start_read(size_t);
    void start_write(size_t, size_t);
    void close_connection(size_t, boost::system::error_code &);
    std::string                         msg;
    std::map<size_t, connection>        connections;
    size_t                              connection_id;
    ip::tcp::endpoint                   endp;
    ip::tcp::acceptor                   acc;
    bool                                started;
    io_service                      &   service;
};
