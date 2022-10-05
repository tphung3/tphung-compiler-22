#!/bin/sh

for good in good*.bminor
do
    if ./bminor -scan $good
    then 
        echo "Good"
    else
        echo "Wrong"
        break
    fi
done

for good in scanner-book-tests/good*.bminor
do
    if ./bminor -scan $good
    then 
        echo "Good"
    else
        echo "Wrong"
        break
    fi
done
