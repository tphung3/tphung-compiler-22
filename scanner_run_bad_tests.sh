#!/bin/sh

for bad in scanner-tests/bad*.bminor
do
    if ./bminor -scan $bad
    then 
        echo "Wrong"
        exit 1
    else
        echo "Bad but this is good"
    fi
done

for bad in scanner-book-tests/bad*.bminor
do
    if ./bminor -scan $bad
    then 
        echo "Wrong"
        exit 1
    else
        echo "Bad but this is good"
    fi
done
