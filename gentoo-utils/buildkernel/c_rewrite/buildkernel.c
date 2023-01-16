#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "buildkernel.h"
#include "strutils.h"
#include "config.h"

int local_flag = 0;
int distccd_flag = 1;
int debug_flag = 0;
int tj = 0;
char kver[50];
char kver_full[100] = "/usr/src/linux-";

char kernel[50];
char sysmap[50];
char config[50];
char initrd[50];
char efi[50];

int yes_no()
{
	char input[50];
    printf("[Y/n]: ");
	while (1)
	{
    	fgets(input, sizeof(input), stdin);
		switch (input[0]) 
		{
            case 'Y':
			case 'y':
                return 1;
            case 'N' :
			case 'n' :
                return 0;
            default:
                printf("[Y/n]: ");
        }
	}
}

int dir_exists(char *path)
{
	if ( path == NULL) return 0;
	DIR *pDir;
    pDir = opendir(path);
	if (pDir != NULL)
	{
		(void) closedir (pDir);
		return 1;
	}
	return 0;
}

void debug(int argc, char *argv[])
{
	if (debug_flag == 1)
	{
		printf("Debug: argc=%d argv[1]=\"%s\" argv[2]=\"%s\"",
        argc, argv[1], argv[2]);
		if (argc > 3) printf(" argv[3]=\"%s\"", argv[3]);
		if (argc > 4) printf(" argv[4]=\"%s\"", argv[4]);
		printf("\n");
		printf("local_flag=%d ",local_flag);
		printf("kver=%s ",kver);
		printf("kver_full=%s\n", kver_full);
	}
}

char *pipe_cmd(char cmd[], size_t size, int rm_newlines)
{
	FILE *p = popen(cmd, "re");
	char *buf = (char *) malloc(size);
    memset(buf, '\0', size);
    char c;
    for (int i = 0; i < size; i++)
    {
        c = getc(p);
        if (c != '\0')
            buf[i] = c;
        else
            break;
    }	
    pclose(p);
    if (rm_newlines >= 1)
        for ( int i = 0; i < size; i++) 
            if (buf[i] == '\n') buf[i] = '\0';
    return buf; 
}

int ping(const char *host)
{
	char cmd[256] = "ping ";
	strcat(cmd, host);
	strcat(cmd, " -c1 -W 0.5 | grep \"100% packet loss\"");
	char *buf = pipe_cmd(cmd, 256, 1);
    if (buf[0] == -1) return 1;
	else return 0;
}

void find_tj()
{
    char *cmd = "rc-service distccd status | grep started";
    char *buf = pipe_cmd(cmd, 50, 1);
    if (buf[0] == '\0') 
    {   
        distccd_flag = 0;
        printf("Service distccd is not started.\n");
        printf("Falling back to localhost mode.\n");
    }
	if (local_flag == 0 && distccd_flag == 1)
	{
		int hostsOnline = 0;
		int l = 0;
		while (hosts[l] != NULL) l++;
		for (int i = 0; i < l; i++) 
		{
			if (ping(hosts[i]) == 1) 
			{
				printf("%s is online.\n", hosts[i]);
				tj += hosts_t[i];
				hostsOnline++;
			}
			else 
			{
				printf("%s is offline.\n", hosts[i]);
			}
		}
		if (hostsOnline <= 1) local_flag = 1;
	}
	else
	{
		char *cmd = "cat /proc/cpuinfo  | grep siblings | sort -u | \
                     awk -F \": \" \'{print $NF}\'";
		char *buf = pipe_cmd(cmd, 50, 1);
		tj = atoi(buf);
	}
}

void move_build()
{
	printf("Todo: move buildfiles\n");
}

void detect_buildfiles()
{
   	system("updatedb");
    memset(kernel, '\0', sizeof(kernel));
	strcpy(kernel, pipe_cmd("locate /boot/vmlinuz-* | grep \"^/boot/\"", 50, 1));
    memset(sysmap, '\0', sizeof(sysmap));
	strcpy(sysmap, pipe_cmd("locate /boot/System.map-* | grep \"^/boot/\"", 50, 1));
    memset(config, '\0', sizeof(config));
	strcpy(config, pipe_cmd("locate /boot/config-* | grep \"^/boot/\"", 50, 1));
    memset(initrd, '\0', sizeof(initrd));
	strcpy(initrd, pipe_cmd("locate /boot/initramfs-* | grep \"^/boot/\"", 50, 1));
    memset(efi, '\0', sizeof(efi));
	strcpy(efi, pipe_cmd("locate Linux | grep \"^/boot/EFI/Linux/linux\"", 50, 1));
	if (efi[0] == -1) strcpy(efi, 
            pipe_cmd("locate /boot/gentoo-linux | grep \"^/boot/gentoo\"", 50, 1));
}

int buildfiles_exist()
{
    if (kernel[0] != (-1 | '\0')) return 1;
    if (sysmap[0] != (-1 | '\0')) return 1;
    if (config[0] != (-1 | '\0')) return 1;
    if (initrd[0] != (-1 | '\0')) return 1;
    if (efi[0] != (-1 | '\0')) return 1;
    return 0;
}

void print_buildfiles(int previous)
{
    if (previous)
        printf("Detected previous buildfiles in /boot:\n");
    else printf("Buildfiles located in /boot:");
    if (kernel[0] != (-1 | '\0')) printf("%s\n", kernel);
    if (sysmap[0] != (-1 | '\0')) printf("%s\n", sysmap);
    if (config[0] != (-1 | '\0')) printf("%s\n", config);
    if (initrd[0] != (-1 | '\0')) printf("%s\n", initrd);
    if (efi[0] != (-1 | '\0')) printf("%s\n", efi);
    printf("\n");

    if (previous)
    {
        printf("Move previous buildfiles before building? (Recommended)\n");
        if (yes_no() == 1) move_build();
    }
}

void build()
{
    detect_buildfiles();
	if (buildfiles_exist()) print_buildfiles(1);
	
    char cmd_base[150] = "cd ";
    sprintf(cmd_base, "cd %s &&", kver_full);
    
    system("eselect kernel list");

    printf("Is this the correct kernel to build?\n");
    if (yes_no() == 0) { printf("Aborted.\n"); return; }
    
    char cmd_clean[250];
    sprintf(cmd_clean, "%s clean", cmd_base);
    printf("\nClean the linux tree?\n");
    if (yes_no() == 1) system(cmd_clean);
    printf("\n");

	find_tj();
    if (1 == local_flag)
        printf ("\nLocalhost mode enabled.\n");
    printf("\nMaking with %d threads...\n", tj);

    char cmd_make[250];
    sprintf(cmd_make, "%s make -j%d CC=\"distcc gcc\"", cmd_base, tj);
    system(cmd_make);

    printf("\nInstalling kernel modules...\n");
    char cmd_modules[250];
    sprintf(cmd_modules, "%s make modules_install", cmd_base);
    system(cmd_modules);

    printf("\nInstalling kernel to /boot...\n");
    char cmd_install[250];
    sprintf(cmd_install, "%s make install", cmd_base);
    system(cmd_install);
}

void initramfs()
{
	printf("Todo: build initramfs\n");
}

void regen_grub()
{
	system("grub-mkconfig -o /boot/grub/grub.cfg");	
}

void detect_kver()
{
        char *cmd ="eselect kernel show | grep src | \
                    awk \'{print $NF}\' | cut -c 16-";
        char *buf = pipe_cmd(cmd, 50, 1);
        strcpy(kver, buf);
        strcat(kver_full, kver);
}

void parse_kver(char *arg)
{
	int len = 0;
	while (ARGS_KVER[len] != NULL)
		len++;
	int i = 0;
	while (i < len)
	{
		if(strncmp(arg,ARGS_KVER[i], strlen(ARGS_KVER[i])) == 0) break;
		i++;
	}
	strcpy(kver, strsplit(arg, strlen(ARGS_KVER[i]), -1));
	strcat(kver_full, kver);
	if (dir_exists(kver_full) == 0)
	{
		memset(kver,'\0', sizeof(kver));
		memset(kver_full, '\0', sizeof(kver_full));
		strcpy(kver_full, "/usr/src/linux-"); 
		printf("\"%s\" argument is trash, \
		using current symlinked kver instead.\n", ARGS_KVER[i]);
    	detect_kver();	
	}
}

void upgrade_kernel()
{
    int valid = 0;
    int input_type = 0;
    char cmd[750] = "ls /usr/src/  | grep \'^linux-\' | cut -c 7- | grep -n \'\'";
    char buf_full[100] = "/usr/src/linux-";
    char *buf = pipe_cmd(cmd, 1000, 0);
	char input_full[100] = "/usr/src/linux-";
    char input[50];
	printf("Current symlinked kernel is %s\nChoose where to copy current kernel config to:\n\n", 
            kver);
    printf("%s\n",buf);
    
    fgets(input, sizeof(input), stdin);
    // sanitize newlines from input
    for (int i = 0; i < strlen(input); i++)
    	if (input[i] == '\n') input[i] = '\0';
    
    strcat(input_full, input);
	
    if (dir_exists(input_full) == 1) 
    {
        input_type = 0;
        valid = 1;
    }
	if (0 == valid && input[0] != '\0')
	{
		strcat(cmd, " | grep \'^");
        strcat(cmd, input);
        strcat(cmd, "\'");
		buf = pipe_cmd(cmd, 1000, 1);
	    
	        if (buf[1] == ':')
        	{ 
            	buf = strsplit(buf, 2, -1);
			    strcat(buf_full, buf);
			    if (dir_exists(buf_full) == 1)
                {
	                input_type = 1;
		            valid = 1;
			    }
	        }
		
	}
    
    if (1 == debug_flag)
    {
        printf("valid=%d\n", valid);
        printf("input_type=%d\n", input_type);
        printf("kver=%s ", kver);
        printf("kver_full=%s\n", kver_full);
        if (input_type == 1)
        {
            printf("buf=%s ", buf);
            printf("buf_full=%s\n", buf_full);
        }
        if (input_type == 0)
        {
            printf("input=%s ", input);
            printf("input_full=%s\n", input_full);
        }
    }
    if (1 == valid)
    {
        if (0 == input_type)
            if (strcmp(input, kver) == 0)
                valid = 0;
        if (1 == input_type)
            if (strcmp(buf, kver) == 0)
                valid = 0;
        if (0 == valid)
            printf("Cannot upgrade to the same kernel version.\n");
    }

    if (1 == valid)
    {
        memset(cmd, '\0', sizeof(cmd));
        strcat(cmd, "cp -v ");
        strcat(cmd, kver_full);
        strcat(cmd, "/.config ");

        if (0 == input_type)
            strcat(cmd, input_full);
        if (1 == input_type)
            strcat(cmd, buf_full );

        strcat(cmd, "/.config");
        printf("\nAre you sure you want to\n\"%s\"?\n",cmd);
        if (yes_no() == 1)
            system(cmd);
        else
            printf("Aborted.\n");
    }
	
}

void check_flags(char *argv[], int argi)
{
	if (strcmp_array(argv[argi], ARGS_LOCAL, 0) == 0) local_flag = 1;
	if (strcmp_array(argv[argi], ARGS_DEBUG, 0) == 0) debug_flag = 1;
	if (strcmp_array(argv[argi], ARGS_KVER, 1) == 0) parse_kver(argv[argi]);	
}

int check_args(int argc, char *argv[])
{
	if (argc == 1 || strcmp_array(argv[1], ARGS_HELP, 0) == 0)
	{
		printf("%s", HELP_PAGE);
		return 0;
	}
	
	if (argc >= 2)
		if (strcmp_array(argv[1], ARGS_DEBUG, 0) == 0) debug_flag = 1;

	if (argc >= 3) check_flags(argv, 2);
	if (argc >= 4) check_flags(argv, 3);
	if (argc >= 5) check_flags(argv, 4);
	
    if (strlen(kver) == 0) detect_kver();

	debug(argc, argv);
	
	if (geteuid() == 0)
	{
		if(strcmp_array(argv[1], ARGS_BUILD, 0) == 0)
		{
       		build();
			return 0;
		}
   		if(strcmp_array(argv[1], ARGS_AUTO, 0) == 0)
		{
		 	build();
			initramfs();
	        move_build();
			regen_grub();
			return 0;
		}
		if(strcmp_array(argv[1], ARGS_INITRD, 0) == 0)
		{
			initramfs();
			return 0;
		}
    		if(strcmp_array(argv[1], ARGS_INITRDMOVE, 0) == 0)
		{
       		initramfs();
			move_build();
			regen_grub();
			return 0;
		}		
		if(strcmp_array(argv[1], ARGS_MOVE, 0) == 0)
		{
			move_build();
			return 0;
		}
		if(strcmp_array(argv[1], ARGS_MENUCONF, 0) == 0)
		{
			char cmd[256] = "cd ";
			strcat(cmd, kver_full);
			strcat(cmd, " && make menuconfig MENUCONFIG_COLOR=mono");
			system(cmd);
			return 0;
		}
		if(strcmp_array(argv[1], ARGS_REGEN, 0) == 0)
		{
			regen_grub();
			return 0;
		}
		if(strcmp_array(argv[1], ARGS_UPGRADE, 0) == 0)
		{
			upgrade_kernel();
			return 0;
		}
	}
	else
	{
		return -1;
	}
	return 1;
}

int main(int argc, char *argv[])
{	
	int exit = check_args(argc, argv);
	if (exit == 0) return 0;
	else
	{
		if (exit == 1) printf("Invalid arguments.\n");
		if (exit == -1) printf("Please run as root.\n");
		return 1;
	}
}
