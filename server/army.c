#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

void	init_criteria(struct addrinfo *crit)
{
  int			protocol;
  struct protoent	*pe;

  if (crit)
    {
      protocol = IPPROTO_TCP;
      if (!(pe = getprotobyname("TCP")))
	fprintf(stderr, "getprotobyname failed, using IPPROTO_TCP.\n");
      else
	protocol = pe->p_proto;
      memset(crit, 0, sizeof(*crit));
      crit->ai_family = AF_INET;
      crit->ai_socktype = SOCK_STREAM;
      crit->ai_protocol = protocol;
    }
}

int	connect_to(char const *name, char const *port)
{
  int			ret;
  int			sock;
  struct addrinfo	crit;
  struct addrinfo	*addr;
  struct addrinfo	*addr_lst;

  sock = -1;
  init_criteria(&crit);
  if ((ret = getaddrinfo(name, port, &crit, &addr_lst)))
    exit(5);
  addr = addr_lst;
  while (addr && sock < 0)
    {
      if ((sock = socket(addr->ai_family, addr->ai_socktype,
			 addr->ai_protocol)) != -1)
	if (connect(sock, addr->ai_addr, addr->ai_addrlen) < 0)
	  close(sock);
      addr = addr->ai_next;
    }
  freeaddrinfo(addr_lst);
  return (sock);
}


int main()
{
  unsigned int i = 0;
  int sock[50];
  char lol[8192];

  for (i = 0; i < sizeof(sock) / sizeof(int); ++i)
    {
      sock[i] = connect_to("localhost", "4242");
      read(sock[i], lol, sizeof(lol));
      write(sock[i], "1\n", sizeof("1\n"));
      read(sock[i], lol, sizeof(lol));
    }
  puts("Army Connected!");
  while (1)
    {
      for (i = 0; i < sizeof(sock) / sizeof(int); ++i)
	{
	  write(sock[i], "avance\n", sizeof("avance\n"));
	  read(sock[i], lol, sizeof(lol));
	}
    }
}
