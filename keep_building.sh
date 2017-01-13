#!/bin/sh -eu

ls main.c build.sh | entr -c ./build.sh
