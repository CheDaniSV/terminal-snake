# Get the latest Git tag
$version = git describe --tags --abbrev=0

# Change dir to ./docs if not here already
cd ./docs

# Replaces @VERSION@ with the actual version in Doxyfile.in and output to Doxyfile
(Get-Content Doxyfile.in) -replace '@VERSION@', $version | Set-Content Doxyfile

# Run Doxygen
doxygen Doxyfile