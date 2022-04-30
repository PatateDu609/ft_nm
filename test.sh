#!/bin/bash

make -s

diff -u --color <(./ft_nm $@ | cat -e) <(nm $@ | cat -e)
if [ $? -eq 0 ]; then
	echo -e "\e[1;32mOK\e[0m"
else
	echo -e "\e[1;31mKO\e[0m"
fi
