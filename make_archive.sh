#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Invalid arguments!"
    exit 1
fi

name=Blatt$1-HeidmannKornbluehKrabbe

tar -cf $name.tar $name --exclude=*.pdf
gzip -9 -f $name.tar
echo "Created $name.tar.gz"
