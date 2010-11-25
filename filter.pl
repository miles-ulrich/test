#!/usr/bin/perl -w

open FILE, "<", $ARGV[0] or die $!;

while (<FILE>) {
    print;
}
