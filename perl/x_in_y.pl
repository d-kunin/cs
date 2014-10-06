# my -- is for local variables of current block

# Scalars

my $animal = "camel";
my $answer = 42;


# Arrays

my @animals = ("camel", "llama", "owl");
my @numbers = (23, 42, 69);
my @mixed = ("camel", 42, 1.23);


# Hashes 

my %fruit_color = ("apple", "red", "banana", "yellow");
# nicer syntax
my %fruit_count = (
    apple => 4,
    banana => 1
);
            
## More on data:
# perldoc perldata


# Flow control
if ($answer == 1) {
    print "It is one!"
} elsif ($answer == 42) {
    print "You know that 42!\n"
} else {
    print %fruit_count
}

unless ($animal eq "pig") {
    print "Camel is the right answer.\n"
}


# Post-condition

print "Wow, it is 42\n" if $answer == 42;
print "It is not pig.\n" unless $animal eq "pig";


# Loops

my $i = 0;
while ($i < 10) {
    print "$i ", $i*$i, "\n";
    $i = $i + 1;
}

for ($i = 1; $i < $answer; $i*=3) {
    print $i, " is not answer\n"
}
print "\n";

foreach my $x (@animals) {
    print "$x is an animal\n";
}

foreach (@numbers) {
    print "$_ is a number\n"
}

print "Number of bananas: $fruit_count{'banana'}\n";




