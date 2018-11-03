#open(my $in,  "<",  "input.txt")  or die "Can't open input.txt: $!";
#open(my $out, ">",  "output.txt") or die "Can't open output.txt: $!";

my @result = ();
my $prev_empty = 0;
while (<>) {
	s/<[^>]*>//g;

	if (/^\s*$/) {
		if ($prev_empty == 0) {
			push(@result, "\n");
		}
		$prev_empty = 1;
	} else {
		s/^\s+//;
		s/\s+$//;
		s/\s+/ /g;

		push(@result, $_ . "\n");
		$prev_empty = 0;		
	}
}

if (@result[0] =~ /^\s*$/) { shift(@result); }
if ((scalar @result) != 0 && @result[(scalar @result) - 1] =~ /^\s*$/) { pop(@result); }

foreach (@result) {
	print $_;
}