#!/bin/bash

# Get the latest Git tag
VERSION=$(git describe --tags --abbrev=0)

# Change dir to ./docs if not here already
cd ./docs

# Replaces @VERSION@ with the actual version in Doxyfile.in and output to Doxyfile
sed "s/@VERSION@/${VERSION}/g" Doxyfile.in > Doxyfile

# Run Doxygen
doxygen Doxyfile