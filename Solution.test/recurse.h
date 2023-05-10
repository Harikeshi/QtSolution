#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#  include <Windows.h>
#else
#  include <sys/stat.h>
#endif

#ifdef _WIN32
const char SEP = '\\';
#else
const char SEP = '/';
#endif

bool recurse_mkdir(const char* dirname)
{
    const char* p;
    char* temp;
    bool        ret = true;

    temp = static_cast<char*>(calloc(1, strlen(dirname) + 1)); 
    /* Skip Windows drive letter. */
#ifdef _WIN32
    if ((p = strchr(dirname, ':')) != NULL)
    {
        p++;
    }
    else {
#endif
        p = dirname;
#ifdef _WIN32
    }
#endif

    while ((p = strchr(p, SEP)) != NULL) {
        /* Skip empty elements. Could be a Windows UNC path or
           just multiple separators which is okay. */
        if (p != dirname && *(p - 1) == SEP) {
            p++;
            continue;
        }
        /* Put the path up to this point into a temporary to
           pass to the make directory function. */
        memcpy(temp, dirname, p - dirname);
        temp[p - dirname] = '\0';
        p++;
#ifdef _WIN32
        if (CreateDirectory((LPCWSTR)temp, NULL) == FALSE) //TODO: cast
        {
            if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
                ret = false;
                break;
            }
        }
#else
        if (mkdir(temp, 0774) != 0) {
            if (errno != EEXIST) {
                ret = false;
                break;
            }
        }
#endif
    }
    free(temp);
    return ret;
}