#!/bin/bash

cd
ls / > f1
ls /usr > f2
mv f1 g1
mv f2 g2
cat g1 g2
tail -4 g1 # tail -n 4 g1
head -3 g2
diff -y g1 g2
rm g2
mkdir dir
mv g1 dir/file
wc -c dir/file
cp dir/file .
rm -r dir