sub GF {
    my $x=shift;
    return 1-$x+$x**2-$x**3+$x**4-$x**5+
           $x**6-$x**7+$x**8-$x**9+$x**10;
}
sub OP($$\@) {
    my $x=shift;
    my $n=(shift)-1;
    my @a=@{(shift)};

    my $v = $a[$n];
    for $i (reverse 1..$n) { $v = $v*($x-$i)+$a[$i-1]; }
    return $v;
}

$pwr = shift || die;        #use $pwr=11 in a n^10 formula

## Calculate the divided difference coefficients
@a=map { GF($_) } (1..$pwr);
for $i (1..$#a) {
    for $j (reverse $i..$#a) { $a[$j]=($a[$j]-$a[$j-1])/$i; }
}

$sum = 0;
for $i (1..$pwr-1) {
    $r = OP($i+1,$i,@a);
    $sum += $r;
    print "OP($i,",$i+1,"): $r\n";
}
print "Sum: $sum\n";