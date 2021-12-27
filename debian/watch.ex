# Example watch control file for uscan
# Rename this file to "watch" and then you can run the "uscan" command
# to check for upstream updates and more.
# See uscan(1) for format

# Compulsory line, this is a version 4 file
version=4

# GitHub hosted projects
opts="filenamemangle=s%(?:.*?)?v?(\d[\d.]*)\.tar\.gz%<project>-$1.tar.gz%" \
   https://github.com/sentrypeer/sentrypeer/tags \
   (?:.*?/)?v?(\d[\d.]*)\.tar\.gz debian uupdate
