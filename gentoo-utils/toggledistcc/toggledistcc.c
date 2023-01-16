#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "strutils.h"
#include "config.h"

size_t j = 0, l = 0;

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

void parse_makeconfig(char *start_makeopts, size_t makeopts_len)
{
    for (int i = 0; i < makeopts_len; i++)
    {
        if (*(start_makeopts + i) == '-')
        {
            if (*(start_makeopts + i + 1) == 'j')
            {
                int jlen = 0; 
                while(*(start_makeopts + i + 1 + jlen) != ' ' && 
                        *(start_makeopts + i + 1 + jlen) != '\"' )
                    jlen++;
                jlen--;
                char *n = malloc(jlen);
                memset(n, '\0', jlen);
                for (int c = 1; c <= jlen; c++)
                {
                    n[c-1] = *(start_makeopts + i + 1 + c);
                }
                n[jlen] = '\0';
                j = atoi(n);
                free(n);
            }
            if (*(start_makeopts + i + 1) == 'l')
            {
                int llen = 0;
                while(*(start_makeopts + i + 1 + llen) != ' ' &&
                        *(start_makeopts + i + 1 + llen) != '\"')
                    llen++;
                llen--;
                char *n = malloc(llen);
                memset(n, '\0', llen);
                for (int c = 1; c <= llen; c++)
                {
                    n[c-1] = *(start_makeopts + i + 1 + c);
                }
                n[llen] = '\0';
                l = atoi(n);
                free(n);
            }   
        }
    }
}

char * get_makeconfig()
{
    FILE* fp;
    fp = fopen("/etc/portage/make.conf", "r");
    size_t length = 0;
    size_t size;

    while (fgetc(fp) != EOF)
            length++;
    size = sizeof(char) * length;

    printf("make.conf is %ld characters long, %ld bytes\n", length, size);

    char *makeconfig = malloc(size+1);
    char c;
    rewind(fp);
    for (int i = 0; i < size; i++)
    {
        c = fgetc(fp);
        makeconfig[i] = c;
    }
    makeconfig[size+1] = '\0';
	fclose(fp);
	return makeconfig;
 
}

void write_makeconfig(char *makeconfig)
{
    FILE* fp;
    fp = fopen("/etc/portage/make.conf", "w");
    size_t length = strlen(makeconfig);
    makeconfig[length] = EOF;
    for (int i = 0; i < length; i++)
        fputc(makeconfig[i], fp);
    fclose(fp);
}

int main()
{
    if (geteuid() != 0)
    {
        printf("Run as root to modify /etc/portage/make.conf\n");
        return 1;
    }

    if (LOCAL_TJ == 0)
	{
		char *cmd = "cat /proc/cpuinfo  | grep siblings | sort -u | \
                     awk -F \": \" \'{print $NF}\'";
        char *buf = pipe_cmd(cmd, 50, 1);
        LOCAL_TJ = atoi(buf);
	    free(buf);
	}	
    
    char *makeconfig = get_makeconfig();

    printf("/etc/portage/make.conf\n\
------------------------\n%s------------------------\n", makeconfig);
    
    char *start_makeopts = strstr(makeconfig, "MAKEOPTS=\"") 
        + strlen("MAKEOPTS=\"");
	char *start_features = strstr(makeconfig, "FEATURES=\"")
        + strlen("FEATURES=\"");
    size_t makeopts_len = 0, features_len = 0;
    while (*(start_makeopts + makeopts_len) != '\"' )
            makeopts_len++;
	while (*(start_features + features_len) != '\"' )
            features_len++;
    
    parse_makeconfig(start_makeopts, makeopts_len);
    printf("(original) -j = %ld  -l = %ld\n", j, l);

    int distcc;
    if (l == 0)
        distcc = 1;
    else
        distcc = 0;  

    if (distcc)
    {
        j = DISTCC_TJ;
        l = LOCAL_TJ;
    }
    else
    {
        l = 0;
        j = LOCAL_TJ;
    }

    int makeopts_index = strstr_index(makeconfig, "MAKEOPTS=\"") + strlen("MAKEOPTS=\"");
	int features_index = strstr_index(makeconfig, "FEATURES=\"") + strlen("FEATURES=\"");

    char *first = strsplit(makeconfig, 0, makeopts_index); 
    char second[100];
    memset(second, '\0', 100);
    char *third = strsplit(makeconfig, (makeopts_index  + makeopts_len), 
                 (features_index - (makeopts_index + makeopts_len)));
    char *fourth = strsplit(makeconfig, features_index, features_len);
    char *fifth = strsplit(makeconfig, (features_index + features_len), -1);
    
    if (distcc)
    {
        sprintf(second, "-j%ld -l%ld", j, l);
        char *fourth_cpy = fourth;
        if (strlen(fourth) < 1)
            sprintf(fourth, "distcc");
        else
            sprintf(fourth, "%s distcc", fourth_cpy);
	printf("Enabling distcc MAKEOPTS and FEATURES...\n");
    }
    else
    {
        sprintf(second, "-j%ld", j); 
        if (strcmp(fourth, "distcc") == 0)
            fourth = "";
        else
            fourth = str_rm(fourth, "distcc", 1);
        printf("Disabling distcc MAKEOPTS and FEATURES...\n");

    }

    size_t size = strlen(first) + strlen(second) + strlen(third) + 
        strlen(fourth) + strlen(fifth) + 1;
    char *newmakeconfig = malloc(size);
    memset(newmakeconfig, '\0', size);
    
    //printf("@@first = \"%s\"\n", first);
    //printf("@@second = \"%s\"\n", second);
	//printf("@@third = \"%s\"\n", third);
	//printf("@@fourth = \"%s\"\n", fourth);
	//printf("@@fifth = \"%s\"\n", fifth);

    sprintf(newmakeconfig,"%s%s%s%s%s", first, second, third, fourth, fifth);
    
    printf("(new) -j = %ld  -l = %ld\n", j, l);
	printf("(new) make.conf is %ld characters long, %ld bytes\n", size, size);
	printf("(new) make.conf\n\
------------------------\n%s------------------------\n", newmakeconfig);

    write_makeconfig(newmakeconfig);
    
    if (distcc)
        system("rc-service distccd restart");
    else
        system("rc-service distccd stop");

    free(makeconfig);
    free(newmakeconfig);
    
    return 0;
}

