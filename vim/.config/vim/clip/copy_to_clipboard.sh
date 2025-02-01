#!/bin/bash

clip_file="$(dirname $0)/.clip"

if [ ! -f "$clip_file" ]; then
	clip_content="WARNING!! CLIP FILE NOT FOUND!"
	echo "WARNING!! CLIP FILE NOT FOUND!"
elif [ ! -s "$clip_file" ]; then
	clip_content="WARNING!! CLIP FILE IS EMPTY!"
	echo "WARNING!! CLIP FILE IS EMPTY!"
else
	clip_content=$(<"$clip_file")
	> "$clip_file"
	echo "Copied to Clipboard!"
fi

encoded_content=$(echo -n "$clip_content" | base64 | tr -d "\n")
echo -e "\033]52;c;${encoded_content}\007"
