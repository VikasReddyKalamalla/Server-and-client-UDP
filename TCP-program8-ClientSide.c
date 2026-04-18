#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    int recv_size;
    char message[1000], server_reply[1000];

    WSAStartup(MAKEWORD(2,2), &wsa);

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(5050);

    connect(s, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to server\n");

    while (1)
    {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        message[strcspn(message, "\n")] = '\0';

        send(s, message, strlen(message), 0);

        recv_size = recv(s, server_reply, sizeof(server_reply)-1, 0);

        if (recv_size <= 0)
        {
            printf("Server disconnected\n");
            break;
        }

        server_reply[recv_size] = '\0';

        printf("Server: %s\n", server_reply);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}