#!/bin/bash

tools=(
    gcc
    g++
    make
    cmake
    gdb
    clang
    clang-format
    git
    docker
    openssl
    ssh
    curl
    wget
    netstat
    nmap
)

echo "Checking essential dev tools on your system..."
echo "----------------------------------------------"

for t in "${tools[@]}"; do
    if command -v "$t" &> /dev/null; then
        echo -e "[✔] $t found"
    else
        echo -e "[✖] $t missing"
    fi
done

echo "----------------------------------------------"
echo "Check complete."
