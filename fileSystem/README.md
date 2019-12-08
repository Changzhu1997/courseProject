## This C program is used to create a new fileSystem based on some changes which can be made to the original V6 file System. V6 file system is highly restrictive. A modification has been done: Block size is 1024 Bytes, i-node size is 64 Bytes and i-node’s structure has been modified as well. This file system is able to store a file which is 4G large. You can also change the size of address array in i-node structure or the way you link data block to the address array (single indirect, double indirect, triple indirect etc.) to store larger file.

## Following are the command i create for this file system. 

## (a) `initfs` fsname n1 n2
fsname is the name of the (external) file in your Unix machine that represents the V6 file system.
n1 is the number of blocks in the disk (fsize) and n2 is the total number of i-nodes.
This command initializes the file system. 
All data blocks are in the free list 
(except for one data blosk that is allocated to the root /. An example is: initfs /user/ChangZhu/disk 800000 300

### (b) `cpin` externalfile v6-file
       Creat a new file called v6-file in the v6 file system and fill the contents of the newly created 
       file with the contents of the externalfile.
### file path for externalfile should be absolute path

## (c) `cpout` v6-file externalfile
If the v6-file exists, create externalfile and make the externalfile's contents equal to v6-file.
### file path for externalfile should be absolute path

## (d) `mkdir` v6-dir
If v6-dir does not exist, create the directory and set its first two entries . and .. 

## (e) `rm` v6-file
If v6-file exists, delete the file, free the i-node, remove the file name from the 
(parent) directory that has this file and add all data blocks of this file to the free list

## (f) `ls`
List the contents of the current directory.

## (g) `pwd`
List the fill pathname of the current directory

## (h) `cd` dirname
change current (working) directory to the dirname

## (i) `rmdir` dir
Remove the directory specified (dir, in this case).

## (j) `openfs` fileSystem
enter the fileSystem create by this program.

## (k) `q`
Save all changes and quit

## There are some bugs by using the system function strcpy to store and show the current path
## But this will not effect the file contents you store in the file system. You can still copy out these files.
