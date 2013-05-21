#!/usr/bin/env perl
use strict;
use warnings;
use Data::Dumper;

# 16-segment display on two shift registers

#    -- --     0  10
#  | \ | / | 2 1 8  9 11
#    -- --     3  12
#  | / | \ | 4 6 7 14 13
#    -- --     5  15

my $display = {
  d00 => [0,2,4,5,10,11,13,15],
  d01 => [7,8],
  d02 => [0,3,4,5,10,11,12,15],
  d03 => [0,3,5,10,11,12,13,15],
  d04 => [2,3,11,12,13],
  d05 => [0,2,3,5,10,12,13,15],
  d06 => [0,2,3,4,5,10,12,13,15],
  d07 => [0,10,11,13],
  d08 => [0,2,3,4,5,10,11,12,13,15],
  d09 => [0,2,3,10,11,12,13],
  d10 => [2,4,7,8,10,11,13,15],
  star => [1,3,6,7,8,9,12,14],
  x => [1,6,9,14],
  plus => [3,7,8,12],
  mode_arm => [9,14],
  zero_01 => [0],
  zero_02 => [10],
  zero_03 => [11],
  zero_04 => [13],
  zero_05 => [15],
  zero_06 => [5],
  zero_07 => [4],
  zero_08 => [2],
  launch_01 => [5,15],
  launch_02 => [3,12],
  launch_03 => [0,10],
  launch_04 => [1,3,6,7,8,9,12,14],
  left_arrow => [4,5,6,9],
  down_arrow => [1,9],
};

my @first_byte;
my @second_byte;

print Dumper $display;
foreach my $key (sort keys %$display) {
  my @segment = @{$display->{$key}};
  my ($byte1, $byte2) = (0,0);
  foreach my $bit (@segment) {
    if ($bit < 8) {
      $byte1 += (1 << (7 - $bit));
    } else {
      $byte2 += (1 << (7 - ($bit - 8)));
    }
  }
  push @first_byte, $byte1;
  push @second_byte, $byte2;
  print "$key: $byte1 $byte2\n";
}

print "const unsigned char digits_byte1[11] = \n  { ";
print join ", ", @first_byte;
print "};\n";

print "const unsigned char digits_byte2[11] = \n  { ";
print join ", ", @second_byte;
print "};\n";
