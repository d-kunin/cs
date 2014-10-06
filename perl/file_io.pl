#!/usr/bin/env perl

open(my $in, "<", "input.txt") or die "Can't open input.txt $!";
open(my $out, ">",  "output.txt") or die "Can't open output.txt: $!";
open(my $log, ">>", "my.log")     or die "Can't open my.log: $!"; 

# read one line
my $line = <$in>;
my @lines = <$in>;

print "$line\n";
print "@lines\n";

foreach my $l (@lines) {
    $l =~ s/^\s+|\s+$//g;
    print $out "that was: $l\n" if (length $l);
    print "lenght of \"$l\" is ", length $l, "\n"; 
}