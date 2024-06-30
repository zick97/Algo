set tics font ",18"
set xlabel "$\\theta$" font ",18"
set ylabel "$v$" font ",18"
set key font ",18" spacing 1.2
set title "Trajectory $v(\\theta)$" font ",18"

set terminal epslatex color colortext
set output "test.tex"

plot "pendulum.txt" using 1:2 index 1 w lp title "RK2", "pendulum.txt" using 1:2 index 0 w lp title "P-V" 

unset output
unset terminal
