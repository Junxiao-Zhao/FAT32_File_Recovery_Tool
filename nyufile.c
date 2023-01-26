/*
References:
All discussion on Discord.
https://blog.csdn.net/knowledgeaaa/article/details/32703317 | SHA1 - SHA1_Init()/SHA1_Update()/SHA1_Final()生成 sha1 散列值函数组合_迷途小码的博客-CSDN博客_sha1_update
https://blog.csdn.net/yishizuofei/article/details/78195255 | C语言中sprintf()函数的用法_yishizuofei的博客-CSDN博客_c语言sprintf函数
https://blog.csdn.net/m0_47696151/article/details/119241140 | sha1 函数 C 语言使用总结_lylhw13_的博客-CSDN博客_c语言sha1函数
https://blog.csdn.net/qq_37734256/article/details/88806744 | C语言读取FAT32分区文件簇链_威化饼的一隅的博客-CSDN博客_簇链
https://blog.csdn.net/taxue4485/article/details/40684703 | C语言Printf格式大全（各种%输出形式）_攻城狮观天下的博客-CSDN博客_c语言printf %
https://stackoverflow.com/questions/41095147/converting-unsigned-char-array-to-hex | c - Converting unsigned char array to hex - Stack Overflow
*/

#include "global.h"

int main(int argc, char *argv[])
{
    unsigned char **command = (unsigned char **)malloc(sizeof(char *) * 4);
    int usage = 0;
    int options[] = {0, 0, 0, 0, 0};
    int ch;

    opterr = 0; // disable the default error message
    // extract options
    while ((ch = getopt(argc, argv, "ilr:R:s:")) != -1)
    {
        switch (ch)
        {
        case 'i':
            options[0]++;
            break;
        case 'l':
            options[1]++;
            break;
        case 'r':
            options[2]++;
            command[0] = optarg;
            break;
        case 'R':
            options[3]++;
            command[0] = optarg;
            break;
        case 's':
            options[4]++;
            command[2] = optarg;
            break;
        }
    }

    // Error if there's erroneous option
    if (optopt)
        usage = 1;
    // Error if more/less than 1 non-option argument
    else if (argc - optind != 1)
        usage = 1;
    else
    {
        int fd = open(argv[optind], O_RDWR, 0644); // file descriptor

        if (fd < 0)
        {
            printf("File not exist");
            return 0;
        }

        // size of the disk
        struct stat buf_size;
        fstat(fd, &buf_size);

        void *addr = mmap(NULL, buf_size.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);

        // -i (0) / -l (1)
        if (options[2] == 0 && options[3] == 0 && options[4] == 0 && (options[0] + options[1] == 1))
        {
            // -i
            if (options[0])
                disk_info(addr);
            // -l
            else
                root_dir(addr, 1, NULL);
        }
        // -r filename (2) / -r filename -s sha1 (3)
        else if (options[2] == 1 && options[0] == 0 && options[1] == 0 && options[3] == 0)
        {
            // -r filename
            if (options[4] == 0)
                root_dir(addr, 2, command);
            // -r filename -s sha1
            else if (options[4] == 1)
                root_dir(addr, 3, command);
        }
        // -R filename -s sha1 (4)
        else if (options[3] == 1 && options[4] == 1 && options[0] == 0 && options[1] == 0 && options[2] == 0)
            root_dir(addr, 4, command);
        else
            usage = 1;

        munmap(addr, buf_size.st_size);
    }

    // Validate Usage
    if (usage)
    {
        printf("Usage: ./nyufile disk <options>\n"
               "  -i                     Print the file system information.\n"
               "  -l                     List the root directory.\n"
               "  -r filename [-s sha1]  Recover a contiguous file.\n"
               "  -R filename -s sha1    Recover a possibly non-contiguous file.\n");
    }

    free(command);
    return 0;
}