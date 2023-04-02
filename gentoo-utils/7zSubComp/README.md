# 7zSubComp

## 7zSubComp stands for 7zip Subdirectory Compression tool

7zSubComp verifies archives after creating them with Ultra LZMA compression. 
```7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on```
7zSubComp can perform extraction, viewing, size information, and removal of subdirectories under a master directory.

```7zSubComp [ -c [-x -e] -r -v ] [ -y ] [directory A]

7zip subdirectory compressor and subdirectory archive extractor.

   -c --compress           -   enter directory A to compress all subdirectories of A into new archives in A.
                               Verifies archive integrity after each archive creation.
   -x -e --extract         -   enter directory A to extract all archives of A into subdirectories in A.
   -r --remove             -   enter directory A to remove all subdirectories of A but save the archives.
   -v --view               -   enter directory A to view all subdirectories and archives of it.
   -y --yes                -   confirm without asking.


Examples:

   7zSubComp -c .      Compress all subdirectories under current directory "." .

   7zSubComp -x .      Extract all archives under current directory "." .

   7zSubComp -r -y .   Remove only subdirectories under current directory "." .
                       Without asking for confirmation (CAREFUL).

   7zSubComp -v .      View subdirectories and archives under current directory "." .

   "." above can be replaced with any directory. Not providing one will ask you for one.
```
### Sample usage
```
will@gentoo /mnt/WD40EFPX-68C/roms/PlayStation λ sudo 7zSubComp -v .

	Archives

'Castlevania - Symphony of the Night (USA).7z'
'Chrono Cross (USA) (Disc 1).7z'
'Chrono Cross (USA) (Disc 2).7z'
'Final Fantasy VII (USA) (Disc 1).7z'
'LSD - Dream Emulator (Japan).7z'
'Metal Gear Solid (USA) (Disc 1) (Rev 1).7z'
'Metal Gear Solid (USA) (Disc 2) (Rev 1).7z'
'Thrasher - Skate and Destroy (USA).7z'
'Tony Hawk'\''s Pro Skater 2 (USA).7z'
'Vagrant Story (USA).7z'

	Subdirectories

'Castlevania - Symphony of the Night (USA)/'
'Chrono Cross (USA) (Disc 1)/'
'Chrono Cross (USA) (Disc 2)/'
'Final Fantasy VII (USA) (Disc 1)/'
'LSD - Dream Emulator (Japan)/'
'Metal Gear Solid (USA) (Disc 1) (Rev 1)/'
'Metal Gear Solid (USA) (Disc 2) (Rev 1)/'
'Thrasher - Skate and Destroy (USA)/'
'Tony Hawk'\''s Pro Skater 2 (USA)/'
'Vagrant Story (USA)/'

.	10.42252642400000000000 GB

Information
-----------
Subdirectories size			:		6.76091461400000000000 GB
Archives size				:		3.66160771400000000000 GB
Delta (Archives - Subdirectories)	:		-3.09930690000000000000 GB
Master directory size			:		10.42252642400000000000 GB

```
```
will@gentoo /mnt/WD40EFPX-68C/roms/PlayStation λ sudo 7zSubComp -c .

'Castlevania - Symphony of the Night (USA)/'
'Chrono Cross (USA) (Disc 1)/'
'Chrono Cross (USA) (Disc 2)/'
'Final Fantasy VII (USA) (Disc 1)/'
'LSD - Dream Emulator (Japan)/'
'Metal Gear Solid (USA) (Disc 1) (Rev 1)/'
'Metal Gear Solid (USA) (Disc 2) (Rev 1)/'
'Thrasher - Skate and Destroy (USA)/'
'Tony Hawk'\''s Pro Skater 2 (USA)/'
'Vagrant Story (USA)/'

.	10.42252642400000000000 GB

10 target subdirectories found.

Current compression settings: 7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on

Start compressing?
[Y/n]: y

[1/10]	Castlevania - Symphony of the Night (USA)	583.33609400000000000000 MB
Creating archive...
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on "Castlevania - Symphony of the Night (USA).7z" "Castlevania - Symphony of the Night (USA)"/

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.utf8,Utf16=on,HugeFiles=on,64 bits,6 CPUs Intel(R) Core(TM) i5-8600K CPU @ 3.60GHz (906EA),ASM,AES-NI)

Open archive: Castlevania - Symphony of the Night (USA).7z
--
Path = Castlevania - Symphony of the Night (USA).7z
Type = 7z
Physical Size = 361787747
Headers Size = 324
Method = LZMA:25
Solid = +
Blocks = 1

Scanning the drive:
1 folder, 4 files, 583331998 bytes (557 MiB)

Updating archive: Castlevania - Symphony of the Night (USA).7z

Items to compress: 5


Files read from disk: 4
Archive size: 361787747 bytes (346 MiB)
Everything is Ok

Verifying integrity of archive...
7z t "Castlevania - Symphony of the Night (USA).7z"

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.utf8,Utf16=on,HugeFiles=on,64 bits,6 CPUs Intel(R) Core(TM) i5-8600K CPU @ 3.60GHz (906EA),ASM,AES-NI)

Scanning the drive for archives:
1 file, 361787747 bytes (346 MiB)

Testing archive: Castlevania - Symphony of the Night (USA).7z
--
Path = Castlevania - Symphony of the Night (USA).7z
Type = 7z
Physical Size = 361787747
Headers Size = 324
Method = LZMA:25
Solid = +
Blocks = 1

Everything is Ok

Folders: 1
Files: 4
Size:       583331998
Compressed: 361787747

[2/10]	Chrono Cross (USA) (Disc 1)	736.65985500000000000000 MB
Creating archive...
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on "Chrono Cross (USA) (Disc 1).7z" "Chrono Cross (USA) (Disc 1)"/

...

[10/10]	Vagrant Story (USA)	750.65189500000000000000 MB
Creating archive...
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on "Vagrant Story (USA).7z" "Vagrant Story (USA)"/

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.utf8,Utf16=on,HugeFiles=on,64 bits,6 CPUs Intel(R) Core(TM) i5-8600K CPU @ 3.60GHz (906EA),ASM,AES-NI)

Open archive: Vagrant Story (USA).7z
--
Path = Vagrant Story (USA).7z
Type = 7z
Physical Size = 70490747
Headers Size = 279
Method = LZMA:25
Solid = +
Blocks = 1

Scanning the drive:
2 folders, 3 files, 750643703 bytes (716 MiB)

Updating archive: Vagrant Story (USA).7z

Items to compress: 5


Files read from disk: 3
Archive size: 70490747 bytes (68 MiB)
Everything is Ok

Verifying integrity of archive...
7z t "Vagrant Story (USA).7z"

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.utf8,Utf16=on,HugeFiles=on,64 bits,6 CPUs Intel(R) Core(TM) i5-8600K CPU @ 3.60GHz (906EA),ASM,AES-NI)

Scanning the drive for archives:
1 file, 70490747 bytes (68 MiB)

Testing archive: Vagrant Story (USA).7z
--
Path = Vagrant Story (USA).7z
Type = 7z
Physical Size = 70490747
Headers Size = 279
Method = LZMA:25
Solid = +
Blocks = 1

Everything is Ok

Folders: 2
Files: 3
Size:       750643703
Compressed: 70490747

Information
-----------
10 archives created and verified in 964 seconds.
Subdirectories size			:		6.76091461400000000000 GB
Archives size				:		3.66160771400000000000 GB
Delta (Archives - Subdirectories)	:		-3.09930690000000000000 GB
Master directory size			:		10.42252642400000000000 GB
```

```
will@gentoo /mnt/WD40EFPX-68C/roms/Super Nintendo λ sudo 7zSubComp -r -y .

	Archives

'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1).7z'
'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr).7z'
'Donkey Kong Country (USA) (Rev 2).7z'
'EarthBound (USA).7z'
'Final Fantasy III (USA) (Rev 1).7z'
'Final Fantasy II (USA) (Rev 1).7z'
'Final Fantasy IV (tr).7z'
'Final Fantasy V (tr).7z'
'F-Zero (USA).7z'
'Harvest Moon (USA).7z'
'Legend of Zelda, The - A Link to the Past (USA).7z'
'Mario Paint (Japan, USA) (En).7z'
'Mega Man X3 (USA).7z'
'Mega Man X (USA) (Rev 1).7z'
'Super Bomberman 2 (USA).7z'
'Super Bomberman 3 (Japan).7z'
'Super Bomberman 4 (Japan).7z'
'Super Bomberman 5 (Japan).7z'
'Super Bomberman (USA).7z'
'Super Ghouls '\''N Ghosts (USA).7z'
'Super Mario RPG - Legend of the Seven Stars (USA).7z'
'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1).7z'
'Super Mario World (USA).7z'
'Super Metroid (Japan, USA) (En,Ja).7z'

	Subdirectories

'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1)/'
'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr)/'
'Donkey Kong Country (USA) (Rev 2)/'
'EarthBound (USA)/'
'Final Fantasy III (USA) (Rev 1)/'
'Final Fantasy II (USA) (Rev 1)/'
'Final Fantasy IV (tr)/'
'Final Fantasy V (tr)/'
'F-Zero (USA)/'
'Harvest Moon (USA)/'
'Legend of Zelda, The - A Link to the Past (USA)/'
'Mario Paint (Japan, USA) (En)/'
'Mega Man X3 (USA)/'
'Mega Man X (USA) (Rev 1)/'
'Super Bomberman 2 (USA)/'
'Super Bomberman 3 (Japan)/'
'Super Bomberman 4 (Japan)/'
'Super Bomberman 5 (Japan)/'
'Super Bomberman (USA)/'
'Super Ghouls '\''N Ghosts (USA)/'
'Super Mario RPG - Legend of the Seven Stars (USA)/'
'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1)/'
'Super Mario World (USA)/'
'Super Metroid (Japan, USA) (En,Ja)/'

.	78.53650200000000000000 MB

24 target subdirectories found.

Are you sure?
[Y/n]: y

[1/24]	"Donkey Kong Country 2 - Diddy's Kong Quest (USA) (En,Fr) (Rev 1)"/
removed 'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1)/Vimm'\''s Lair.txt'
removed 'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1)/Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1).sfc'
removed directory 'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1)/'

[2/24]	"Donkey Kong Country 3 - Dixie Kong's Double Trouble! (USA) (En,Fr)"/
removed 'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr)/Vimm'\''s Lair.txt'
removed 'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr)/Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr).sfc'
removed directory 'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr)/'

[3/24]	"Donkey Kong Country (USA) (Rev 2)"/
removed 'Donkey Kong Country (USA) (Rev 2)/Donkey Kong Country (USA) (Rev 2).sfc'
removed 'Donkey Kong Country (USA) (Rev 2)/Vimm'\''s Lair.txt'
removed directory 'Donkey Kong Country (USA) (Rev 2)/'

[4/24]	"EarthBound (USA)"/
removed 'EarthBound (USA)/Vimm'\''s Lair.txt'
removed 'EarthBound (USA)/EarthBound (USA).sfc'
removed directory 'EarthBound (USA)/'

[5/24]	"Final Fantasy III (USA) (Rev 1)"/
removed 'Final Fantasy III (USA) (Rev 1)/Vimm'\''s Lair.txt'
removed 'Final Fantasy III (USA) (Rev 1)/Final Fantasy III (USA) (Rev 1).sfc'
removed directory 'Final Fantasy III (USA) (Rev 1)/'

[6/24]	"Final Fantasy II (USA) (Rev 1)"/
removed 'Final Fantasy II (USA) (Rev 1)/Final Fantasy II (USA) (Rev 1).sfc'
removed 'Final Fantasy II (USA) (Rev 1)/Vimm'\''s Lair.txt'
removed directory 'Final Fantasy II (USA) (Rev 1)/'

[7/24]	"Final Fantasy IV (tr)"/
removed 'Final Fantasy IV (tr)/Vimm'\''s Lair.txt'
removed 'Final Fantasy IV (tr)/ff4ev321.txt'
removed 'Final Fantasy IV (tr)/Final Fantasy 4 (tr).sfc'
removed directory 'Final Fantasy IV (tr)/'

[8/24]	"Final Fantasy V (tr)"/
removed 'Final Fantasy V (tr)/readme.txt'
removed 'Final Fantasy V (tr)/Vimm'\''s Lair.txt'
removed 'Final Fantasy V (tr)/Final Fantasy 5 (tr).sfc'
removed directory 'Final Fantasy V (tr)/'

[9/24]	"F-Zero (USA)"/
removed 'F-Zero (USA)/Vimm'\''s Lair.txt'
removed 'F-Zero (USA)/F-Zero (USA).sfc'
removed directory 'F-Zero (USA)/'

[10/24]	"Harvest Moon (USA)"/
removed 'Harvest Moon (USA)/Vimm'\''s Lair.txt'
removed 'Harvest Moon (USA)/Harvest Moon (USA).sfc'
removed directory 'Harvest Moon (USA)/'

[11/24]	"Legend of Zelda, The - A Link to the Past (USA)"/
removed 'Legend of Zelda, The - A Link to the Past (USA)/Vimm'\''s Lair.txt'
removed 'Legend of Zelda, The - A Link to the Past (USA)/Legend of Zelda, The - A Link to the Past (USA).sfc'
removed directory 'Legend of Zelda, The - A Link to the Past (USA)/'

[12/24]	"Mario Paint (Japan, USA) (En)"/
removed 'Mario Paint (Japan, USA) (En)/Vimm'\''s Lair.txt'
removed 'Mario Paint (Japan, USA) (En)/Mario Paint (Japan, USA) (En).sfc'
removed directory 'Mario Paint (Japan, USA) (En)/'

[13/24]	"Mega Man X3 (USA)"/
removed 'Mega Man X3 (USA)/Vimm'\''s Lair.txt'
removed 'Mega Man X3 (USA)/Mega Man X3 (USA).sfc'
removed directory 'Mega Man X3 (USA)/'

[14/24]	"Mega Man X (USA) (Rev 1)"/
removed 'Mega Man X (USA) (Rev 1)/Vimm'\''s Lair.txt'
removed 'Mega Man X (USA) (Rev 1)/Mega Man X (USA) (Rev 1).sfc'
removed directory 'Mega Man X (USA) (Rev 1)/'

[15/24]	"Super Bomberman 2 (USA)"/
removed 'Super Bomberman 2 (USA)/Vimm'\''s Lair.txt'
removed 'Super Bomberman 2 (USA)/Super Bomberman 2 (USA).sfc'
removed directory 'Super Bomberman 2 (USA)/'

[16/24]	"Super Bomberman 3 (Japan)"/
removed 'Super Bomberman 3 (Japan)/Super Bomberman 3 (Japan).sfc'
removed 'Super Bomberman 3 (Japan)/Vimm'\''s Lair.txt'
removed directory 'Super Bomberman 3 (Japan)/'

[17/24]	"Super Bomberman 4 (Japan)"/
removed 'Super Bomberman 4 (Japan)/Vimm'\''s Lair.txt'
removed 'Super Bomberman 4 (Japan)/Super Bomberman 4 (Japan).sfc'
removed directory 'Super Bomberman 4 (Japan)/'

[18/24]	"Super Bomberman 5 (Japan)"/
removed 'Super Bomberman 5 (Japan)/Super Bomberman 5 (Japan).sfc'
removed 'Super Bomberman 5 (Japan)/Vimm'\''s Lair.txt'
removed directory 'Super Bomberman 5 (Japan)/'

[19/24]	"Super Bomberman (USA)"/
removed 'Super Bomberman (USA)/Super Bomberman (USA).sfc'
removed 'Super Bomberman (USA)/Vimm'\''s Lair.txt'
removed directory 'Super Bomberman (USA)/'

[20/24]	"Super Ghouls 'N Ghosts (USA)"/
removed 'Super Ghouls '\''N Ghosts (USA)/Vimm'\''s Lair.txt'
removed 'Super Ghouls '\''N Ghosts (USA)/Super Ghouls '\''N Ghosts (USA).sfc'
removed directory 'Super Ghouls '\''N Ghosts (USA)/'

[21/24]	"Super Mario RPG - Legend of the Seven Stars (USA)"/
removed 'Super Mario RPG - Legend of the Seven Stars (USA)/Vimm'\''s Lair.txt'
removed 'Super Mario RPG - Legend of the Seven Stars (USA)/Super Mario RPG - Legend of the Seven Stars (USA).sfc'
removed directory 'Super Mario RPG - Legend of the Seven Stars (USA)/'

[22/24]	"Super Mario World 2 - Yoshi's Island (USA) (Rev 1)"/
removed 'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1)/Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1).sfc'
removed 'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1)/Vimm'\''s Lair.txt'
removed directory 'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1)/'

[23/24]	"Super Mario World (USA)"/
removed 'Super Mario World (USA)/Super Mario World (USA).sfc'
removed 'Super Mario World (USA)/Vimm'\''s Lair.txt'
removed directory 'Super Mario World (USA)/'

[24/24]	"Super Metroid (Japan, USA) (En,Ja)"/
removed 'Super Metroid (Japan, USA) (En,Ja)/Vimm'\''s Lair.txt'
removed 'Super Metroid (Japan, USA) (En,Ja)/Super Metroid (Japan, USA) (En,Ja).sfc'
removed directory 'Super Metroid (Japan, USA) (En,Ja)/'

	Archives

'Donkey Kong Country 2 - Diddy'\''s Kong Quest (USA) (En,Fr) (Rev 1).7z'
'Donkey Kong Country 3 - Dixie Kong'\''s Double Trouble! (USA) (En,Fr).7z'
'Donkey Kong Country (USA) (Rev 2).7z'
'EarthBound (USA).7z'
'Final Fantasy III (USA) (Rev 1).7z'
'Final Fantasy II (USA) (Rev 1).7z'
'Final Fantasy IV (tr).7z'
'Final Fantasy V (tr).7z'
'F-Zero (USA).7z'
'Harvest Moon (USA).7z'
'Legend of Zelda, The - A Link to the Past (USA).7z'
'Mario Paint (Japan, USA) (En).7z'
'Mega Man X3 (USA).7z'
'Mega Man X (USA) (Rev 1).7z'
'Super Bomberman 2 (USA).7z'
'Super Bomberman 3 (Japan).7z'
'Super Bomberman 4 (Japan).7z'
'Super Bomberman 5 (Japan).7z'
'Super Bomberman (USA).7z'
'Super Ghouls '\''N Ghosts (USA).7z'
'Super Mario RPG - Legend of the Seven Stars (USA).7z'
'Super Mario World 2 - Yoshi'\''s Island (USA) (Rev 1).7z'
'Super Mario World (USA).7z'
'Super Metroid (Japan, USA) (En,Ja).7z'

.	27.55733600000000000000 MB

Information
-----------
24 archives removed in 0 seconds.
Subdirectories size			:		0 bytes
Archives size				:		27.55324000000000000000 MB
Original Master directory size		:		78.53650200000000000000 MB
New Master directory size		:		27.55733600000000000000 MB
Delta					:		-50.97916600000000000000 MB
```

