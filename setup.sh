#!/bin/bash

echo "[*] Setting up TUIL environment..."

# 1. Build the static library and the user application
echo "[1/2] Building library and testing compilation..."
make all

echo ""
echo "[+] Setup complete! You are good to go."
echo "------------------------------------------------------"
echo "  > To compile your own code   : run 'make'"
echo "  > To run your program        : run './main'"
echo "  > To install system-wide     : run 'sudo make install'"
echo "------------------------------------------------------"
