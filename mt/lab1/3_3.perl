open(my $in,  "<",  "input.txt")  or die "Can't open input.txt: $!";
# open(my $out, ">",  "output.txt") or die "Can't open output.txt: $!";

my $input = "";
while (<$in>) {
	$input = $input . $_;	
}

my %result = ();
while ($input =~ /<\s*[aA].+\bhref\s*=\s*"\s*([^"]*)\s*".*>/) {
	$match = $1;

	$match =~ /(?<scheme>([^:\/?#]+:)?\/\/)?(\w+(:\w+)?@)?(?<host>[^:\/?#]+)(?<port>\:\d+)?([:\/?#].*)?/i;
	
	$scheme = $+{scheme};
	$port = $+{port};
	$host = $+{host};
	if (!($scheme =~ /^\s*$/) || !($port =~ /^\s*$/)) {
		$result{$host} = 1;
	}

	$input =~ s/<\s*[aA].+\bhref\s*=\s*("\s*([^"]*)\s*"|'\s*([^"]*)\s*').*>//;	
}

foreach $host (sort(keys %result)) {
    if (!($host =~ /^\s*$/)) {
        print $host . "\n";
    }
}