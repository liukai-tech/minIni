#include "lfs.h"                   /* include lfs.h for littlefs */
#include "string.h"

extern lfs_t lfs;

char *lfs_gets(char *s, int size, lfs_file_t *file)
{
    char    *ptr;
    int32_t numBytes;
    int32_t pos;

    if ((s == 0) || (size <= 0))
    {
        return(NULL);
    }
    /* See the current position before reading */
    pos = lfs_file_seek(&lfs, file, 0, LFS_SEEK_CUR);
    /* Read from the current position */
    numBytes = lfs_file_read(&lfs, file, (s), (size - 1));
    if (numBytes > 0)
    {
        /* Find the first/next new line */
        ptr = strchr(s, '\n');
        if (ptr)
        {
            ptr++;
            *ptr = 0;
            numBytes = strlen(s);
        }
    }
    else
    {
        return(NULL);
    }
    assert(numBytes <= size);
    /* Set the new position for the next read */
    lfs_file_seek(&lfs, file, (pos + numBytes), LFS_SEEK_SET);
    return(s);
}
