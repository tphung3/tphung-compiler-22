#!/bin/sh

for good in scanner-tests/good*.bminor
do
    if ./bminor -scan $good
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done

for good in scanner-book-tests/good*.bminor
do
    if ./bminor -scan $good
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done
