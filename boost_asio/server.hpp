#pragma once

class echo_server
{
public:
    echo_server(io_service &);
    void start_accept();
    void stop_accept();
    echo_server(echo_server &) = delete;
    const echo_server & operator=(echo_server &) = delete;
private:
    struct connection
    {
        boost::shared_ptr<ip::tcp::socket> sock_ptr;
        char buf[BUF_SIZE + 1];
        connection() = default;
        connection(io_service &service) : 
            sock_ptr(new ip::tcp::socket(service))
            {
                buf[BUF_SIZE] = '\0';
            }
        /*connection(connection &con)
        {
            sock_ptr = std::move(con.sock_ptr);
            buf[BUF_SIZE] = '\0';
        }*/
    };
    void start_read(size_t);
    void start_write(size_t, size_t);
    void close_connection(size_t);
    std::map<size_t, connection>    connections;
    size_t                          connection_id;
    ip::tcp::endpoint               endp;
    ip::tcp::acceptor               acc;
    bool                            started;
    io_service                      &service;
};
