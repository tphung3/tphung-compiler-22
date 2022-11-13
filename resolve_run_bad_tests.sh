#!/bin/sh

for bad in typecheck-book-tests/bad*.bminor
do
    echo "---------------"
    echo $bad
    if ./bminor -resolve $bad
    then 
        echo "Wrong"
        #exit 1
    else
        echo "Bad but this is good"
    fi
done
