# 1
#while (<>) {
#	s/human/computer/g;
#	print;
#}

# 2
#while (<>) {
#	s/\bhuman\b/computer/g;
#	print;
#}

# 3
#while (<>) {
#	s/\b[aA]+\b/argh/;
#	print;
#}

# 4
#while (<>) {
#	s/(\w+)(\W+)(\w+)/$3$2$1/;
#	print;
#}

# 5
#while (<>) {
#	s/(\w)(\w)(\w*)/$2$1$3/g;
#	print;
#}

# 6
#while (<>) {
#	s/(\w)(\1)/$1/g;
#	print;
#}

# 7
#while (<>) {
#	s/(\w)(\1+)/$1/g;
#	print;
#}

# 8
#while (<>) {
#	s/\b(\d+)0\b/$1/g;
#	print;
#}

# 9
#while (<>) {
#	s/\([^)]*\)/\(\)/g;
#	print;
#}

# 10
while (<>) {
	s/(a.*?a)(a.*?a)(a.*?a)/bad/g;
	print;
}
