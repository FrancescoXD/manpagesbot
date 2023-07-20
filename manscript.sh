#!/bin/bash

mansubs() {
	man "$1" |col -bx|awk '/^[A-Z ]+$/ {print}'
}

manedit() {
	man "$1" |col -bx|awk -v S="$2" '$0 ~ S {cap="true"; print} $0 !~ S && /^[A-Z ]+$/ {cap="false"} $0 !~ S && !/^[A-Z ]+$/ {if(cap == "true")print}'
}

mansubs
manedit
