#!/usr/bin/env perl

#  documentation in perlrequick, perlretut,


# Simple matching

my @names = ("Dima", "Anna", "Patrick", "Bob");

foreach (@names) {
    print "Here is $_!\n" if (/Dima/);
}

foreach my $x (@names) {
    print "Here is not Dima: $x\n" unless ($x =~ /Dima/);
}


# Substitution
foreach my $name (@names) {
    my $fixed_name = $name;
    $fixed_name =~ s/[iae]/o/g;
    print "$fixed_name is $name\n";
}



