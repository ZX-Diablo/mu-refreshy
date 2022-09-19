# mu-refreshy

[![Build Status](https://github.com/ZX-Diablo/mu-refreshy/actions/workflows/build-test-coverage.yml)](https://github.com/ZX-Diablo/mu-refreshy/actions/workflows/build-test-coverage.yml/badge.svg)
[![Build Status](https://travis-ci.org/ZX-Diablo/mu-refreshy.svg?branch=master)](https://travis-ci.org/ZX-Diablo/mu-refreshy)
[![Coverage Status](https://coveralls.io/repos/github/ZX-Diablo/mu-refreshy/badge.svg?branch=master)](https://coveralls.io/github/ZX-Diablo/mu-refreshy)

## What is it

_mu-refreshy_ is a small program made to help refreshing music collection.

I have quite a big music collection and it's hard and time consuming to keep it up to date.  
I couldn't find suitable solution so decided to write this instrument.  
Basically it tries to answer simple question: which artists have released new albums since last time I checked.

Keep in mind that I made this program just to solve my problem in the simplest way so it's not user-friendly at all.

## How it works

1. _mu-refreshy_ scans your music library to get info about what artists and albums you have
2. For every artist call to [musicbrainz](https://musicbrainz.org/) is made to get full albums list (assuming it is full; unfortunately it's not, so better go and contribute there)
3. Results are printed on console or into xml file, all remote albums with release date older than your local ones are considered as new
4. You can use xml file for future calls, all remote albums would be considered as local

## Example

Contents of artist folder (just one for example):

![files](https://i.imgur.com/hClY8kW.jpg "Artist files")

Program text result:

![txt](https://i.imgur.com/crfYABL.jpg "Text result")

Result in xml format (part of it):

![xml](https://i.imgur.com/W2s5MZr.jpg "XML result")

It takes about 40 minutes to process around 3000 files in 8 threads.

## Building

Only UNIX (I'm using Gentoo, Ubuntu also would work because travis).  
Requirements:
* [g++](https://gcc.gnu.org/) supporting C++11 (not sure about minimum version, travis is using 4.8.4)
* [CMake](https://cmake.org/) >= 3.0
* [Boost](http://www.boost.org/) >= 1.79.0
* [libmusicbrainz](https://musicbrainz.org/doc/libmusicbrainz)
* [TagLib](http://taglib.org/)
* [pugixml](http://pugixml.org/)

```shell
mkdir build && cd build
cmake ..
make
```

Binary in `bin/mu-refreshy`.

## Usage

### Synopsis

`mu-refreshy [options] <root>`

**root** specifies directory with music files. Also can be set through options.

### Options

- `-h` `--help` print help info
- `-r <path>` `--root=<path>` set root directory with music files, required, can be set without flag
- `-s <method>` `--scan=<method>` set directory scan method, default is all files, see more info below
- `-i <file>` `--file=<file>` set input xml file to read additional data from previous runs
- `-f (txt|xml)` `--format=(txt|xml)` set output format, plain text or xml file, default is text
- `-t <number>` `--thread=<number>` set amount of threads for parallel file processing, default is 8

### Scan methods

- `all` scan all files in given root directory and it's subdirectories
- `album` faster method for organized collections. Scan one file per sub-subdirectory. Works only if you have \<artist\>/\<album\> structure
- `artist` special case for my personal needs, probably useless to everyone else. In the root are unsorted files and artist subdirectories (without album sub-subdirectories).
Scan only files inside subdirectories.

### Examples

`mu-refreshy --scan=all -t 1 "/mnt/music/In Flames" 2>/dev/null`

Scan all files in given directory in one thread and output results on console in plain text.

`mu-refreshy --scan=artist --format=xml "/mnt/music/" >result.xml`

Scan files inside artist subdirectories in multiple threads and store results in xml file.

`mu-refreshy --format=xml --file=result.xml "/mnt/music/In Flames" >result2.xml`

Scan all files in given directory using additional data from previous run and store results in new xml file.

## Future plans

Probably would not develop it further because problem solved.
But if I return to it anytime at least there is a plan what to do.

- [ ] Contribute info to musicbrainz
- [ ] Ignore case when comparing albums
- [ ] Use remote albums info to update local albums to get more precise dates and results (also ignore case in name comparison)
- [ ] Windows cross-compilation support. At least working precompiled executable
- [ ] Service virtualization usage to avoid calling to musicbrainz in tests
- [ ] Configurable musicbrainz endpoint
- [ ] Main application source decomposition and test coverage
- [ ] Automatic artist disambiguation mechanism (take artist with the most releases, for example)
- [ ] Filtering by album type
- [ ] musicbrainz answers caching (actually good for only not found queries so can be simplified)
- [ ] Maybe add some kind of profiling

## Known issues

- Local albums ID and type are always empty
- Local albums release date is always on the first of january (only year info), so they can appear as new
- Remote albums with unknown release date are on 1970-01-01
- There can be several remote artist IDs, only way to resolve it is to fiddle with xml files
