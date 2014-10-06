#!/usr/bin/env perl

sub logger {
    my $logmessage = shift;
    open my $logfile, ">>", "my.log" or die "Could not open my.log: $!";
    print $logfile $logmessage;
}

logger("We have a logger subroutine!");

# perlfaq contains questions and answers related to many common tasks, 
# and often provides suggestions for good CPAN modules to use.