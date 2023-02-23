#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <config.h>

char *net_file;
char *new_net_file;
char *search_term_dhcp;
char *search_term_static;
bool bad_config;
size_t index_dhcp;
size_t index_static;

char *get_net()
{
	FILE *fptr = fopen("/etc/conf.d/net", "r");
	if (!fptr) 
	{
		fprintf(stderr, "Error opening `/etc/conf.d/net`.\n");
		exit(1);
	}

	fseek(fptr, 0L, SEEK_END);
	size_t size = ftell(fptr) + 1;
	rewind(fptr);
	
	char *buf = malloc(size);
	buf[size-1] = 0;
	
	size_t i = 0;
	char f_char = fgetc(fptr);
	while (f_char != EOF) 
	{
		buf[i++] = f_char;
		f_char = fgetc(fptr);
	}
	fclose(fptr);
	return buf;
}

void write_net(char *new)
{
	FILE *fptr = fopen("/etc/conf.d/net", "w");
	if (!fptr)
	{
		fprintf(stderr, "Error opening `/etc/conf.d/net`.\n");
		exit(1);
	}
	
	size_t length = strlen(new);
	new[length] = EOF;
	
	for (int i = 0; i < length; i++)
	{
		fputc(new[i], fptr);
	}
	fclose(fptr);
}

void print_sep()
{
	for (int i = 0; i < 10; i++)
		printf("-");
	printf("\n");
}

void check_config(const char *iface)
{
	bad_config = false;
	if (search_term_dhcp) free(search_term_dhcp);
	asprintf(&search_term_dhcp, "config_%s=\"dhcp\"", iface);
	if (!strstr(net_file, search_term_dhcp)) bad_config = true;
	index_dhcp = strstr(net_file, search_term_dhcp) - net_file;
	
	if (search_term_static) free(search_term_static);
	asprintf(&search_term_static, "config_%s=\"192.168.", iface);	
	if (!strstr(net_file, search_term_static)) bad_config = true;
	index_static = strstr(net_file, search_term_static) - net_file;

	if (bad_config) 
	{
		print_sep();
		if (!strstr(net_file, search_term_dhcp)) 
			fprintf(stderr, "ERROR: Could not find `%s`\n", search_term_dhcp);
		if (!strstr(net_file, search_term_static)) 
			fprintf(stderr, "ERROR: Could not find `%s`\n", search_term_static);
		free(search_term_dhcp);
		free(search_term_static);
		free(net_file);
		exit(1);
	}
}

void create_new_net_file(const char *iface)
{
	check_config(iface);
	print_sep();
	if (new_net_file) free(new_net_file);
	new_net_file = calloc(1, strlen(net_file) + 4);
	if (index_dhcp && net_file[index_dhcp - 1] == '#')
	{
		printf("**Enabling dhcp for interface %s**\n", iface);
		int a = 0;
		if (index_dhcp > 1)
			for (int i = 0; i < index_dhcp - 1; i++)
				new_net_file[a++] = net_file[i];
		for (int i = index_dhcp; i < index_static - 1; i++)
			new_net_file[a++] = net_file[i];
		new_net_file[a++] = '\n';
		new_net_file[a++] = '#';
		for (int i = index_static; i < strlen(net_file); i++)
			new_net_file[a++] = net_file[i];
	}
	else if (index_static && net_file[index_static - 1] == '#')
	{
		printf("**Disabling dhcp for interface %s**\n", iface);
		int a = 0;
		if (index_dhcp > 1)
			for (int i = 0; i < index_dhcp; i++)
				new_net_file[a++] = net_file[i];
		new_net_file[a++] = '#';
		for (int i = index_dhcp; i < index_static - 1; i++)
			new_net_file[a++] = net_file[i];
		for (int i = index_static; i < strlen(net_file); i++)
			new_net_file[a++] = net_file[i];
	}
	else exit(1);
	//printf("index_dhcp = %ld\n", index_dhcp);
	//printf("index_static = %ld\n", index_static);
	write_net(new_net_file);
}

int main()
{	
	net_file = get_net();
	print_sep();
	printf("/etc/conf.d/net\n");
	print_sep();
	printf("%s", net_file);
	
	
	int iface_size = 0;
	while (dhcp_interface[iface_size] != NULL)
		iface_size++;

	for (int i = 0; i < iface_size; i++)
	{
		create_new_net_file(dhcp_interface[i]);		
		if (i < iface_size)
		{
			free(net_file);
			net_file = get_net();
		}
		if (i == iface_size - 1)
		{
			printf("new /etc/conf.d/net\n");
			print_sep();
			printf("%s", new_net_file);
		}
	}
	

	free(search_term_dhcp);
	free(search_term_static);
	free(net_file);
	free(new_net_file);

	return 0;
}


