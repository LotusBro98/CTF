#!/bin/bash/

chars=$(cat $(ls $1) | tr -d '\n')
echo $chars
