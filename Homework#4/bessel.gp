reset

set title "Bessel Function (nu = 1) with yL = 0, yR = 1" font ",18"
# 1st plot, numerical & analytical solution
set xlabel "x" font ",18"
set ylabel "y(x)" font ",18"

set terminal epslatex color colortext
set output "bessel.tex"

plot "bessel.txt" u 1:2 w lp title "Tridiagonal", besj1(x)/besj1(10.0) title "Exact"

unset output
unset terminal
