#!/usr/bin/perl -w

use Time::HiRes qw/ time sleep /;

# Use loop to print all args stored in an array called @ARGV
my $args = "";
my $i = 1;
while ($i < @ARGV) {
	$args = $args . " " . $ARGV[$i];
	$i = $i + 1;
}

my $start = time;
system("./$ARGV[0] $args > $ARGV[0].out");
my $end = time;
my $run_time = $end - $start;
print "$run_time\n";
