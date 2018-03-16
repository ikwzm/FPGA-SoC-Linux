
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
