#!/bin/bash

foo() {
    
    if [ "${#COMP_WORDS[@]}" != "2" ]; then
        return
    fi

    COMPREPLY=($(compgen -W "one two three"))


}

complete -F foo mycommand
