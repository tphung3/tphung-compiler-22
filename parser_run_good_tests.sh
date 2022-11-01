#!/bin/sh

for good in parser-book-tests/good*.bminor
do
    echo $good
    if ./bminor -parse $good
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done

for good in parser-tests/good*.bminor
do
    echo $good
    if ./bminor -parse $good
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done
