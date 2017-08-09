#pragma once

class echo_client
{
public:
    echo_client() = default;
    echo_client(const echo_client &);
    echo_client(io_service &, std::string &);
    void start();
private:
    void start_read(size_t, size_t);
    void start_write(size_t, size_t);
    char                        buf[BUF_SIZE + 1];
    std::string                 msg;
    boost::shared_ptr<sock>     sock_;
    ip::tcp::endpoint           endp;
};