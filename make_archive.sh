#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Invalid arguments!"
    exit 1
fi

name=Blatt$1-HeidmannKornbluehKrabbe

echo "Creating tar ball..."
tar -cf $name.tar $name --exclude=*.pdf --exclude=__pycache__

echo "Gzipping tar ball..."
gzip -9 -f $name.tar

echo "Created $name.tar.gz"
echo "Done!"

exit 0
