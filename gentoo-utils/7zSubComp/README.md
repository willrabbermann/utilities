# 7zSubComp

## 7zSubComp stands for 7zip Subdirectory Compression tool

7zSubComp verifies integrity of archives after creating them with Ultra LZMA compression. 

```7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on```

7zSubComp can perform compression, extraction, viewing the directory structure, accurate size information, accurate size differential after operations, and removal of subdirectories under a master directory. At the current time it dumps everything into subdirectories without full paths.

```7zSubComp [ -c [-x -e] -r -v ] [ -y ] [directory A]

7zip subdirectory compressor and archive extractor for 7z archives.

   -c --compress           -   enter directory A to compress all subdirectories of A into new archives in A.
                               Verifies archive integrity after each archive creation.
   -x -e --extract         -   enter directory A to extract all archives of A into subdirectories in A.
   -r --remove             -   enter directory A to remove only subdirectories under A.
   -v --view               -   enter directory A to view size info and all subdirectories and archives of A.
   -y --yes                -   confirm without asking.


Examples:

   7zSubComp -c .      Compress all subdirectories under current directory "." .

   7zSubComp -x .      Extract all archives under current directory "." .

   7zSubComp -r -y .   Remove only subdirectories under current directory "." .
                       without asking for confirmation. With "7zSubComp -r -y" it will still ask once.

   7zSubComp -v .      View subdirectories and archives under current directory "." .

   "." above can be replaced with any directory. Not providing one will ask you for one.
```
