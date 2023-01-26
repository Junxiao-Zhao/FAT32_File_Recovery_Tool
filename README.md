## FAT32 File Recovery Tool 

A Tool to recover accidentally deleted files on FAT32 disk. This tool could: 

- Extract the information and accessed files in the disk
- Recover large contiguously-allocated file
- Detect ambiguous file recovery requests and recover the right file with SHA-1 hash

Commands:

        [root@... cs202]# ./nyufile
        Usage: ./nyufile disk <options>
          -i                     Print the file system information.
          -l                     List the root directory.
          -r filename [-s sha1]  Recover a contiguous file.
          -R filename -s sha1    Recover a possibly non-contiguous file.
