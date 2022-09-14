#!/bin/sh

for bad in bad*.bminor
do
    if ./bminor -scan $bad
    then 
        echo "Wrong"
        break
    else
        echo "Bad but this is good"
    fi
done
