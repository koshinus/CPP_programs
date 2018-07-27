#include <boost/asio.hpp>
#include <iostream>
#include "../common/utilities.hpp"

char buffer[1024];
char message[256];
char option[1];
const char sending_machine_addr[] = "127.0.0.1";
const uint16_t sending_machine_port = 6868;
uint32_t ipv4_addr[4];
uint32_t target_machine_addr;
uint16_t target_machine_port;
uint64_t id, block_len, offset, msg_len;
struct sockaddr_in send_addr;

int main()
{
    boost::asio::io_service service;
    ///*    
    while(1)
    {
        printf("Wait for option symbol: ");
        // We need to ignore the newline symbol after the input
        scanf("%s", option);
        if (!(option[0] == 'p' || option[0] == 't'))
            return 0;
        else
        {
            printf("Enter the block id: ");
            scanf("%lu", &id);
            printf("Enter offset in block: ");
            scanf("%lu", &offset);
            printf("Enter the length of a piece of data in the block: ");
            scanf("%lu", &msg_len);
            if (option[0] == 'p')
            {
                printf("Print full length of block: ");
                scanf("%lu", &block_len);
                printf("Print message: ");
                scanf("%s", message);
                fill_buffer(buffer, option[0], id, block_len, offset, msg_len, 0, 0, message);
            }
            else if (option[0] == 't')
            {
                printf("Enter ip address of target machine: ");
                scanf("%u.%u.%u.%u", &ipv4_addr[3], &ipv4_addr[2], &ipv4_addr[1], &ipv4_addr[0]);
                target_machine_addr = ipv4_addr[0] | ipv4_addr[1] << 8 | ipv4_addr[2] << 16 | ipv4_addr[3] << 24;
                printf("Enter port of target machine: ");
                scanf("%hu", &target_machine_port);
                fill_buffer(buffer, option[0], id, 0, offset, msg_len, target_machine_addr, target_machine_port, NULL);
            }
            namespace asio_ip = boost::asio::ip;
            asio_ip::udp::socket send_sock(service);
            send_sock.open(boost::asio::ip::udp::v4());
            send_sock.set_option(boost::asio::socket_base::broadcast(true));
            asio_ip::udp::endpoint dest(asio_ip::address::from_string(sending_machine_addr), sending_machine_port);
            send_sock.async_send_to(boost::asio::buffer(buffer), dest,
                                    [](const boost::system::error_code & e, size_t bytes_transfered)
                                    {
                                       if (e || !bytes_transfered)
                                           std::cout << "Error on receive from client.";
                                    });
        }
    }
    service.run();
    //*/
    return 0;
}

