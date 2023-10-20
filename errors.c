#include "ft_malcolm.h"

int is_hex (char c)
{
	if (c >= 'a' && c <= 'f')
		return (0);
	else if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int is_mac (char *str)
{
	for (int i = 0 ; i < 17 ; i++)
	{
		if ((i + 1) % 3 && is_hex(str[i]))
			return (1);
		else if ((i + 1) % 3 == 0 && str[i] != ':')
			return (1);
	}
	if (str[17])
		return (1);
	return (0);
}

int atoi_i (char *str, int *i)
{
	int n = 0;

	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + str[*i] - '0';
		(*i)++;
	}
	return (n);
}

int is_ip (char *str)
{
	int i = 0;

	for (int x = 0 ; x < 4 ; x++)
	{
		int n = atoi_i(str, &i);
		if (n < 0 || n > 255)
			return (1);

		if (x != 3 && str[i++] != '.')
			return (1);
		else if (x == 3 && str[i] != 0)
			return (1);
	}
	return (0);
}

int is_verbose (char *str)
{
	if (!str)
		return (1);

	if (strcmp(str, "-v") && strcmp(str, "--verbose"))
		return (1);
	return (0);
}

int error_check (int ac, char **av)
{
	if (getuid() != 0)
		printf("ft_malcolm: user is non-root (must have root privileges)\n");
	else if ((ac != 5 && ac != 6) || (ac == 6 && is_verbose(av[5])))
		printf("ft_malcolm: usage: sudo ./ft_malcolm <probed IP> <spoofed MAC> <sender IP> <sender MAC>\n\tIP format is 1.1.1.1, MAC format is aa:bb:cc:dd:ee:ff\n\tfirst argument is the IP you ping, second is the MAC address you want to spoof,\n\tthird and fourth arguments are identifiers of the machine doing the pinging\n");
	else if (is_ip(av[1]))
		printf("ft_malcolm: first argument is invalid ip address (%s)\n", av[1]);
	else if (is_mac(av[2]))
		printf("ft_malcolm: second argument is invalid mac address (%s)\n", av[2]);
	else if (is_ip(av[3]))
		printf("ft_malcolm: third argument is invalid ip address (%s)\n", av[3]);
	else if (is_mac(av[4]))
		printf("ft_malcolm: fourth argument is invalid mac address (%s)\n", av[4]);
	else
		return (0);
	return (1);
}