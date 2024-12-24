/*  Glue functions for the minIni library, based on the littlefs
 *  libraries, see https://github.com/littlefs-project/littlefs
 *
 *  By guangjieMVP, 2022
 *  This "glue file" is in the public domain. It is distributed without
 *  warranties or conditions of any kind, either express or implied.
 *
 *  (The littlefs libraries are copyright by ARM and licensed at
 *  its own terms.)
 */
#ifndef _MINGLUE_LFS_H_
#define _MINGLUE_LFS_H_

#define INI_BUFFERSIZE  256       /* maximum line length, maximum path length */

/* You must set FF_USE_STRFUNC to 1 or 2 in the include file ff.h (or tff.h)
 * to enable the "string functions" fgets() and fputs().
 */
#include "lfs.h"                   /* include lfs.h for littlefs */
#include "stdio.h"
#include "string.h"

/* 定义一行文本结束符  */
#define INI_LINETERM      "\n"

/* 使用库自带的strnicmp*/
#define PORTABLE_STRNICMP

extern lfs_t lfs;

char *lfs_gets(char *s, int size, lfs_file_t *file);

#define INI_FILETYPE    lfs_file_t
#define ini_openread(filename, file)    (lfs_file_open(&lfs, (file), (filename), LFS_O_RDONLY | LFS_O_CREAT) == LFS_ERR_OK)
#define ini_openwrite(filename, file)   (lfs_file_open(&lfs, (file), (filename), LFS_O_WRONLY | LFS_O_CREAT) == LFS_ERR_OK)
#define ini_close(file)                 (lfs_file_close(&lfs, file) == LFS_ERR_OK)
#define ini_read(buffer, size, file)    (lfs_gets((buffer), (size), (file)))
#define ini_write(buffer, file)         (lfs_file_write(&lfs, (file), (buffer), strlen(buffer)))
#define ini_remove(filename)            (lfs_remove(&lfs, filename) == LFS_ERR_OK)
#define ini_rename(source, dest)        (lfs_rename(&lfs, (source), (dest)) == LFS_ERR_OK)

#define INI_FILEPOS                     lfs_soff_t
#define ini_tell(file, pos)             (*(pos) = lfs_file_tell(&lfs, (file)))
#define ini_seek(file, pos)             (lfs_file_seek(&lfs, (file), *(pos), LFS_SEEK_SET) == LFS_ERR_OK)

#endif
