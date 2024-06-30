reset

set title "Absolute error" font ",18"
# 1st plot, numerical & analytical solution
set xlabel "x" font ",18"
set ylabel "Delta y(x)" font ",18"

set terminal epslatex color colortext
set output "delta.tex"

plot "bessel.txt" u 1:($2-besj1($1)/besj1(10.0)) title "Error"

unset output
unset terminal
