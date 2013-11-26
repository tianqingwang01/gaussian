#!/usr/bin/perl -w
use strict;
use warnings;

####Usage: perl rand.pl NUM_TO_GENERATE MAX_LENGTH

my $total=shift;
my $maxLength=shift;

for (my $i=0; $i<$total; $i++){

	my @a = (0..9,'a'..'z','A'..'Z');
	my $password=join '',map { $a[int rand @a] } 0..($maxLength-1);
	print "$password\n";
}
