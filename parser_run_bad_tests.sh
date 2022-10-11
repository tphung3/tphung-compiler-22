#!/bin/sh

for bad in parser-book-tests/bad*.bminor
do
    if ./bminor -parser $bad
    then 
        echo "Wrong"
        exit 1
    else
        echo "Bad but this is good"
    fi
done

for bad in bad*.bminor
do
    if ./bminor -parser $bad
    then 
        echo "Wrong"
        exit 1
    else
        echo "Bad but this is good"
    fi
done

