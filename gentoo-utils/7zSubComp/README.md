# 7zSubComp

## 7zSubComp stands for 7zip Subdirectory Compression tool

7zSubComp can preform compression, extraction, viewing the directory structure, accurate size information, accurate size differential after operations, and removal of subdirectories under a master directory. 

Retain full directory paths when extracting from 7z, zip, rar, and zstd.

Create either 7z or zstd archives with ```--compress=7z``` or ```--compress=zstd```
Extract with ```--extract``` or ```--extract={type}``` to extract only a type of archive.

View current directory structure, archives, and size differential information with ```--view```.

### gentoo dependencies
```app-arch/p7zip rar``` use flag is required if you want to be able to extract ```rar``` files, but it is proprietary.

7zSubComp will extract 7z, zip, rar, or zstd archives.

7zSubComp will compress subdirectories into either 7zip ```.7z``` or ZSTD ```.tar.zstd``` archives.

```
7zSubComp [ [ -c={type} ] [-e -e={type} ] -r -v ] [ -y ] [directory A]

7z/zstd subdirectory compressor and 7z/zip/rar/zstd archive extractor.

Compressing
   -c={type} --compress={type}    -   enter directory A to compress all subdirectories of A into new archives in A.
   type={ 7z, zstd }                  Verifies archive integrity after each archive creation.

Decompressing
   -e --extract                  -   enter directory A to extract all archives of A into subdirectories in A.
   -e={type} --extract={type}        Extract only one type with "-e={type}" or "--extract={type}" .
   type={ 7z, zip, rar, zstd }

Removing
   -r --remove             -   enter directory A to remove only subdirectories under A.

Viewing
   -v --view               -   enter directory A to view size info and all subdirectories and archives of A.

Other
   -y --yes                -   confirm without asking.

Examples:

   7zSubComp -c=7z .       -   Compress all subdirectories under current directory "." into 7z archives.

   7zSubComp -e .          -   Extract all archives under current directory "." .
   7zSubComp -e=zstd .     -   Extract all zstd archives under current directory "." .

   7zSubComp -r -y .       -   Remove only subdirectories under current directory "."
                               without asking for confirmation. With "7zSubComp -r -y" it will still ask once.

   7zSubComp -v .          -   View subdirectories and archives under current directory "." .

   "." above can be replaced with any directory. Not providing one will ask you for one.

```
