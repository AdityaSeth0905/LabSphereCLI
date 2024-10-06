#!/bin/bash

# Get the latest tag
latest_tag=$(git describe --tags `git rev-list --tags --max-count=1`)
version=${latest_tag:1}  # Remove the 'v' from the version
IFS='.' read -r major minor patch <<< "$version"

# Increment patch version
patch=$((patch + 1))
new_version="$major.$minor.$patch"

# Create a new tag
git tag "v$new_version"
echo "New version tagged: v$new_version"
