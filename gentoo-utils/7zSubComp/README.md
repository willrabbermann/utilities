# 7zSubComp
version 1.16

## 7zSubComp stands for 7zip Subdirectory Compression tool
Made for Gentoo Linux but anyone could run 7zSubComp as long as you have the dependencies listed below.

7zSubComp can preform compression, extraction, viewing the directory structure, accurate size information, accurate size differential after operations, and removal of subdirectories under a master directory. 

Retain full directory paths when compressing/extracting to/from 7z, zip, rar, and zstd.

Set the output directory for extraction and compression operations using ```--output={PATH}``` or ```-o {PATH}```

Create either 7z or zstd archives with ```--compress=7z``` or ```--compress=zstd```

Extract all archives with ```--extract``` or ```--extract={type}``` to extract only a single type of archive.

View current directory structure, archives, and size differential information with ```--view```.

7zSubComp always asks the user if they want to overwrite the subdirectory (extracting) or archive (compressing) unless the ```--yes``` operator is  given.

### Linux (Gentoo) dependencies
```app-arch/p7zip rar``` use flag is required if you want to be able to extract .rar archives, however, it is proprietary.

```app-arch/zstd``` and ```app-arch/tar``` is required if you want to extract or compress archives as .tar.zst (zstd) archives. 

GNU Core Utilities should be installed, especially: ```bash``` ```grep``` ```egrep``` ```bc``` ```du``` ```wc``` ```free``` ```cut``` ```echo``` ```cat``` ```sort``` ```ls``` ```pwd```.

```
7zSubComp [ [ -c={type} ] [-e -e={type} ] -r -v ] [ -y ] [directory A] [ -o ] [directory B]
Release version: 1.16

7z/zstd subdirectory compressor and 7z/zip/rar/zstd archive extractor.

Compressing
   -c={type} --compress={type}    -   Enter directory A to compress all subdirectories of A into new archives in A.
   type={ 7z, zstd }                  Verifies archive integrity after each archive creation.

Decompressing
   -e -x --extract                      -   Enter directory A to extract all archives of A into subdirectories in A.
   -x={type} -e={type} --extract={type}     Extract only one type with "-e={type}" or "--extract={type}" .
   type={ 7z, zip, rar, zstd }

Removing
   -r --remove             -   Enter directory A to remove only subdirectories under A.

Viewing
   -v --view               -   Enter directory A to view size info and all subdirectories and archives of A.

Other
   -y --yes                -   Confirm without asking.

   -o {PATH} -o={PATH}                  -   Set the output path (relative or absolute).
   --output {PATH} --output={PATH}          No input defaults to directory A.

Examples:

   7zSubComp -c=7z .       -   Compress all subdirectories under current directory "." into 7z archives.

   7zSubComp -e .          -   Extract all archives under current directory "." .
   7zSubComp -e=zstd .     -   Extract all zstd archives under current directory "." .
   7zSubComp -e=zstd . -o extract
                           -   Extract all zstd archives under current directory "." to output directory "extract".

   7zSubComp -r -y .       -   Remove only subdirectories under current directory "."
                               without asking for confirmation. With "7zSubComp -r -y" it will still ask once.

   7zSubComp -v .          -   View subdirectories and archives under current directory "." .

   "." above can be replaced with any directory. Not providing one will ask you for one.

```
## Known issues
There is no way to set output/input directories which include spaces of any kind. I could fix it if I get around to it. 
