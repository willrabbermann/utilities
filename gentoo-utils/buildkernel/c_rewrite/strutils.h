#ifndef STRUTILS_H
#define STRUTILS_H

char *strsplit(char *str,int offset, int length);
int strstr_index(char *str1, char *str2);
int strcmp_array(char *a, const char *b[], int n);
char *str_rm(char *str1, char *str2, int limit_spaces);

char *strsplit(char *str,int offset, int length)
// Split string with offset and length. 
// char *str = "Hello world"
// (str, 2, -1) == "llo world"
// (str, -1, 2) == "Hello Wor"
{
    int alen;
    int newsize = length;
    alen = strlen(str);
    if(offset > alen 
        || length > alen 
        || (offset + length) > alen
        || (offset == -1 && length == -1))
        return "\0";
    if (-1 == length) 
    {
        length = alen - offset;
        newsize = length;
    }
    else if (-1 == offset)
        newsize = alen - length;
    
    char *newstr = malloc(sizeof(char) * (newsize + 1));
    if (-1 != offset)
    {
        int i = 0;
        for (int c = offset; c < (offset + length); c++)
        {
            newstr[i] = str[c];
            i++;
        }
    }
    else if (-1 == offset)
    {
        for (int i = alen - length - 1; i >= 0; i--)
            newstr[i] = str[i];
    }
    newstr[newsize] = '\0';
    return newstr;
}

int strstr_index(char *str1, char *str2)
// Returns the index of the first occurance of
// (needle) str2 in (haystack) str1
{
    char *result = strstr(str1, str2);
    int index = result - str1;
    return index;
}

int strcmp_array(char *a, const char *b[], int n )
// Returns 0 if char *a is equal to an element in char *b[]. 
// Returns 1 if not equal; -1 with invalid input.
// b[] must be NULL terminated. 
// If n is 1, perform strncmp up to strlen(b[i]) bytes (a starts with b[i]).
// If n is 0, perform strcmp (a == b[i]).
{
    if (n < 0 || n > 1) return -1;
    int len = 0;
    while (b[len] != NULL)
        len++;
    for (int i = 0; i < len; i++)
    {
        if (n == 0 && strcmp(a, b[i]) == 0)
            return 0;
        if (n == 1 && strncmp(a, b[i], strlen(b[i])) == 0)
            return 0;
    }
    return 1;
}

char *str_rm(char *str1, char *str2, int limit_spaces)
// Remove all occurences of str2 in str1.
// Returns a pointer to the final string.
// Returns null if str2 > str1.
//
// limit_spaces == 1 will limit spaces to 
// one per word throughout the final string.
// Also removes trailing/beginning space characters.
{
    if (strlen(str2) > strlen(str1)) return NULL;
    size_t str1_size = sizeof(char) * strlen(str1);
    char *str1_cpy = malloc(str1_size);
    memcpy(str1_cpy, str1, str1_size);
    size_t occurances = 0;
    
    while (1)
    {
        char *found_str2 = strstr(str1_cpy, str2);
        int index = found_str2 - str1_cpy;
        if (found_str2 != NULL)
        {
            occurances++;
            for (int i = index; i < (index + strlen(str2)); i++)
                str1_cpy[i] = EOF;
        }
        else break;
    }
    
    size_t size = sizeof(char) * (strlen(str1) - (occurances * strlen(str2)));
    
    char *newstr = malloc(size);
    memset(newstr , '\0', size);
    int a = 0, newstr_len = size;
    for (int i = 0; i < str1_size; i++)
    {
        if (str1_cpy[i] != EOF)
        {
            newstr[a] = str1_cpy[i];
            a++;
        }
    }
    if (limit_spaces)
    {
        free(str1_cpy);
        int space = 0, spaces = 0;
        // mark beginning and word spaces
        for (int i = 0; i < strlen(newstr); i++)
    	{
	    	if (newstr[i] == ' ')
   		    {
            	if (space || i == 0) 
                {   
                    spaces++;
                    newstr[i] = EOF;
                    space = 1;
                }
            	else space = 1;
        	}
            else if (newstr[i] != EOF)
                space = 0;
        }
        // mark trailing spaces
        for (int i = strlen(newstr) - 1; i >= 0; i--)
        {
            if (newstr[i] == ' ')
            {
                spaces++;
                newstr[i] = EOF;
            }
            else if (newstr[i] != EOF)
                break;
        }
        size = sizeof(char) * (newstr_len - spaces + 1);
        char *space_limited = malloc(size);
        memset(space_limited, '\0', size);
        a = 0;
        for (int i = 0; i < newstr_len; i++)
        {
            if (newstr[i] != EOF)
            {
                space_limited[a] = newstr[i];
                a++;
            }
        }
        free(newstr);
        return space_limited;
    }
    else
    {
        free(str1_cpy);
        return newstr;
    }
}
#endif
