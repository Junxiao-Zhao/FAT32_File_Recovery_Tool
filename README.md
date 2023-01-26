## FAT32 File Recovery Tool 

A Tool to recover accidentally deleted files on FAT32 disk. This tool could: 

- Extracted the information and accessed files in the disk
- Recovered large contiguously-allocated file
- Detected ambiguous file recovery requests and recovered the right file with SHA-1 hash

Commands:

        [root@... cs202]# ./nyufile
        Usage: ./nyufile disk <options>
          -i                     Print the file system information.
          -l                     List the root directory.
          -r filename [-s sha1]  Recover a contiguous file.
          -R filename -s sha1    Recover a possibly non-contiguous file.
