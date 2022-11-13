#!/bin/sh

if ./scanner_run_good_tests.sh &> /dev/null
then
    echo "scanner good passed"
else
    echo "scanner good wrong"
    exit 1
fi

if ./scanner_run_bad_tests.sh &> /dev/null
then
    echo "scanner bad passed"
else
    echo "scanner bad wrong"
    exit 1
fi

if ./parser_run_good_tests.sh &> /dev/null
then
    echo "parser good passed"
else
    echo "parser good wrong"
    exit 1
fi

if ./parser_run_bad_tests.sh &> /dev/null
then
    echo "parser bad passed"
else
    echo "parser bad wrong"
    exit 1
fi

if ./printer_run_good_tests.sh &> /dev/null
then
    echo "printer good passed"
else
    echo "printer good wrong"
    exit 1
fi

if ./printer_run_bad_tests.sh &> /dev/null
then
    echo "printer bad passed"
else
    echo "printer bad wrong"
    exit 1
fi

if ./typecheck_run_good_tests.sh &> /dev/null
then
    echo "typecheck good passed"
else
    echo "typecheck good wrong"
    exit 1
fi

if ./typecheck_run_bad_tests.sh &> /dev/null
then
    echo "typecheck bad passed"
else
    echo "typecheck bad wrong"
    exit 1
fi
