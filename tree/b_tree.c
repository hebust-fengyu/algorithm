#include <stdio.h>
#include <Windows.h>
#include<winsock.h>



#pragma comment(lib, "ws2_32.lib")


int main(void)
{
	char** pptr;
	struct hostent* hptr;
	char str[32] = { 0 };
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	char* ptr = "www.baidu.com";


	if ((hptr = gethostbyname(ptr)) == NULL)
	{
		printf("gethostbyname error: %s\n", ptr);
		return 0;
	}

	printf("official hostname:%s\n", hptr->h_name);   //主机规范名
	printf("the host ip length: %d\n", hptr->h_length);
	for (int i = 0; i < hptr->h_length ; ++i) {
		printf("the index is %d,", i);
		if ((hptr->h_addr_list)[i] == NULL) {
			printf("the indexis null", i);
			continue;
		}
		char* c = inet_ntoa(*((struct in_addr*)((hptr->h_addr_list)[i])));
		printf("the index host ip is:%d\n", c);
	}



	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)   //将主机别名打印出来
		printf("alias: %s\n", *pptr);

	switch (hptr->h_addrtype)  //根据地址类型，将地址打印出来
	{
	case AF_INET:

	default:
		printf("unkown address type\n");
		break;
	}

	return 0;
}
