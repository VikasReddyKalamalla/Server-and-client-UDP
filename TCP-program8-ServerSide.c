#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char buffer[1000];

    WSAStartup(MAKEWORD(2,2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5050);

    bind(s, (struct sockaddr *)&server, sizeof(server));

    listen(s, 3);

    printf("Server started... Waiting for client...\n");

    c = sizeof(client);
    new_socket = accept(s, (struct sockaddr *)&client, &c);

    printf("Client connected!\n");

    while (1)
    {
        recv_size = recv(new_socket, buffer, sizeof(buffer)-1, 0);

        if (recv_size <= 0)
        {
            printf("Client disconnected\n");
            break;
        }

        buffer[recv_size] = '\0';

        printf("Client: %s\n", buffer);

        send(new_socket, buffer, recv_size, 0);
    }

    closesocket(new_socket);
    closesocket(s);
    WSACleanup();

    return 0;
}