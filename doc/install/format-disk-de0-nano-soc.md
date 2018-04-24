#### Format SD-Card for DE0-Nano-Soc

##### Delete old partitions

````console
shell# fdisk /dev/sdc
Command (m for help): d
Selected partition 1
Partition 1 has been deleted.

Command (m for help): w
The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.

shell#
````

##### Create new partions

There are tree ways

1. run scripts/format-disk-zynq.sh
2. run fdisk step-by-step (not discussed hear)
3. run other tools(not discussed hear)


###### scripts/format-disk-de0-nano-soc.sh

````sh:scripts/format-disk-de0-nano-soc.sh
sed -e 's/\s*\([\+0-9a-zA-Z]*\).*/\1/' << EOF | fdisk ${DISKDEV}
  o     # clear the in-memory partition table
  n     # new partition
  p     # primary partition
  3     # partition number 3
        # default - start at beginning of disk
  +8M   # 8 MiB boot partition
  t     # change type partition
  a2    # 0xa2 to type of partition number 3
  n     # new partition
  p     # primary partition
  1     # partition number 1
        # default - start at beginning of disk
  +100M # 100 MB boot partition
  t     # change type partition
  1     # partition number 1
  b     # VFAT to type of partition number 1
  n     # new partition
  p     # primary partition
  2     # partition number 2
        # default - start immediately after preceding partition
        # default - extend partition to end of disk
  p     # print the in-memory partition table
  w     # write the partition table
  q     # and we're done
EOF
````

````console
shell# export DISKDEV=/dev/sdc
shell# sh scripts/format-disk-de0-nano-soc.sh

Welcome to fdisk (util-linux 2.25.2).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.


Command (m for help): Created a new DOS disklabel with disk identifier 0x90c55c12.

Command (m for help): Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): Partition number (1-4, default 1): First sector (2048-61765631, default 2048): Last sector, +sectors or +size{K,M,G,T,P} (2048-61765631, default 61765631): 
Created a new partition 3 of type 'Linux' and of size 8 MiB.

Command (m for help): Selected partition 3
Hex code (type L to list all codes): Changed type of partition 'Linux' to 'unknown'.

Command (m for help): Partition type
   p   primary (1 primary, 0 extended, 3 free)
   e   extended (container for logical partitions)
Select (default p): Partition number (1,2,4, default 1): First sector (18432-61765631, default 18432): Last sector, +sectors or +size{K,M,G,T,P} (18432-61765631, default 61765631): 
Created a new partition 1 of type 'Linux' and of size 100 MiB.

Command (m for help): Partition number (1,3, default 3): Hex code (type L to list all codes): 
If you have created or modified any DOS 6.x partitions, please see the fdisk documentation for additional information.
Changed type of partition 'Linux' to 'W95 FAT32'.

Command (m for help): Partition type
   p   primary (2 primary, 0 extended, 2 free)
   e   extended (container for logical partitions)
Select (default p): Partition number (2,4, default 2): First sector (223232-61765631, default 223232): Last sector, +sectors or +size{K,M,G,T,P} (223232-61765631, default 61765631): 
Created a new partition 2 of type 'Linux' and of size 29.4 GiB.

Command (m for help): Disk /dev/sdc: 29.5 GiB, 31624003584 bytes, 61765632 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x90c55c12

Device     Boot  Start      End  Sectors  Size Id Type
/dev/sdc1        18432   223231   204800  100M  b W95 FAT32
/dev/sdc2       223232 61765631 61542400 29.4G 83 Linux
/dev/sdc3         2048    18431    16384    8M a2 unknown

Partition table entries are not in disk order.

Command (m for help): The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.

````

##### Create file systems

````console
shell# mkfs.vfat /dev/sdc1
shell# mkfs.ext3 /dev/sdc2
````

