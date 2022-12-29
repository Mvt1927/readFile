#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

void do_ls(char dirname[], int flagID = 0)
{
    int PATH_MAX = 1024;
    DIR *dir_ptr;
    if (!(dir_ptr = opendir(dirname)))
    {
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
        return;
    }
    struct dirent *direntp;
    while ((direntp = readdir(dir_ptr)))
    {
        struct stat buf;
        char path[PATH_MAX];
        snprintf(path, PATH_MAX, "%s/%s", dirname, direntp->d_name);
        if (stat(path, &buf))
        {
            fprintf(stderr, "stat failed\n");
            break;
        }
        printf("name    : %s\n", direntp->d_name);
        if (flagID == 1)
        {
            printf("mode    : %o\n", buf.st_mode);   /* type + mode */
            printf("links   : %ld\n", buf.st_nlink); /* # links     */
            printf("user    : %d\n", buf.st_uid);    /* user id     */
            printf("group   : %d\n", buf.st_gid);    /* group id    */
            printf("size    : %ld\n", buf.st_size);  /* file size   */
            printf("modtime : %ld\n", buf.st_mtime); /* modified    */
            printf("path    : %s\n", path);          /* filename    */
        }
    }
    closedir(dir_ptr);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        do_ls(".");
        return 0;
    }
    if (argc > 1)
    {
        if (argc == 2)
        {
            if (strcmp(argv[1], "-a")==0)
            {
                do_ls(".",1);
                return 0;
            }
            else
            {
                do_ls(argv[1]);
                return 0;
            }
            return 0;
        }
        else
        {
            if (strcmp(argv[1], "-a")==0)
            {
                for (size_t i = 2; i < argc; i++)
                {
                    printf("Read %s:\n", argv[i]);
                    do_ls(argv[i],1);
                }
                return 0;
            }
            else
            {
                for (size_t i = 1; i < argc; i++)
                {
                    printf("Read %s:\n", argv[i]);
                    do_ls(argv[i]);
                }
                return 0;
            }
        }
    }

    return 0;
}