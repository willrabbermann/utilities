# 7zSubComp
version 1.105

## 7zSubComp stands for 7zip Subdirectory Compression tool
Made for Gentoo Linux.

7zSubComp can preform compression, extraction, viewing the directory structure, accurate size information, accurate size differential after operations, and removal of subdirectories under a master directory. 

Retain full directory paths when compressing/extracting to/from 7z, zip, rar, and zstd.

Create either 7z or zstd archives with ```--compress=7z``` or ```--compress=zstd```

Extract all archives with ```--extract``` or ```--extract={type}``` to extract only a single type of archive.

View current directory structure, archives, and size differential information with ```--view```.

### gentoo dependencies
```app-arch/p7zip rar``` use flag is required if you want to be able to extract ```rar``` files, however, it is proprietary.

Other dependencies required:
```bash``` ```grep``` ```egrep``` ```bc``` ```app-arch/zstd``` 

```
7zSubComp [ [ -c={type} ] [-e -e={type} ] -r -v ] [directory A] [ -o ] [directory B] [ -y ]
Release version: 1.105

7z/zstd subdirectory compressor and 7z/zip/rar/zstd archive extractor.

Compressing
   -c={type} --compress={type}    -   Enter directory A to compress all subdirectories of A into new archives in A.
   type={ 7z, zstd }                  Verifies archive integrity after each archive creation.

Decompressing
   -e --extract -x                        -   Enter directory A to extract all archives of A into subdirectories in A.
   -x={type} -e={type} --extract={type}   -   Extract only {type}.
   type={ 7z, zip, rar, zstd }

Removing
   -r --remove             -   Enter directory A to remove only subdirectories under A.

Viewing
   -v --view               -   Enter directory A to view size info and all subdirectories and archives of A.

Other
   -y --yes                -   Confirm without asking.
   -o {directory B}        -   Set the output directory for compressing or extracting to directory B.

Examples:

   7zSubComp -c=7z .             -   Compress all subdirectories under current directory "." into 7z archives.
   7zSubComp -c=7z . -o ~/test   -   Compress all subdirectories under current directory "." into 7z archives inside "~/test".

   7zSubComp -e .                -   Extract all archives under current directory "." .
   7zSubComp -e=zstd .           -   Extract all zstd archives under current directory "." .
   7zSubComp -x . -o ~/test      -   Extract all archives under current directory "." to "~/test".

   7zSubComp -r -y .             -   Remove only subdirectories under current directory "."
                                     without asking for confirmation. With "7zSubComp -r -y" it will still ask once.

   7zSubComp -v .                -   View subdirectories and archives under current directory "." .

   "." above can be replaced with any directory. Not providing one will ask you for one.

 ```
