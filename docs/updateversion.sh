#!/bin/bash

# Default: enable check format
CHECK_FORMAT=true

# Parse arguments
VERSION=""
if [[ $# -ge 1 ]]; then
    VERSION="$1"
    shift
fi

while [[ $# -gt 0 ]]; do
    case "$1" in
        --no-check-format)
            CHECK_FORMAT=false
            shift
            ;;
        *)
            echo "Unknown argument: $1"
            exit 1
            ;;
    esac
done

# If no version was provided, get latest git tag
if [[ -z "$VERSION" ]]; then
    VERSION=$(git describe --tags --abbrev=0)
fi

# Check version format if needed
if $CHECK_FORMAT; then
    if [[ ! "$VERSION" =~ ^v[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
        echo "Invalid version format! Must be like v1.2.3"
        exit 1
    fi
else
    echo "Version format is ignored!"
fi

# Change dir to script dir (./docs)
cd $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

echo "Using version: $VERSION"

# Replace @VERSION@ in Doxyfile.in and output to Doxyfile
sed "s/@VERSION@/$VERSION/g" Doxyfile.in > Doxyfile