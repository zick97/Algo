reset
# -- Set plot environment --
# -- Set font size --
set tics font ",18"
set xlabel "t" font ",18"
set ylabel "E(t)" font ",18"
set key font ",18" spacing 1.2
set title "Energy" font ",18"

plot "harmonic.txt" using 1:2 index 0 ps 0 w lp title "Position-Verlet"
replot "harmonic.txt" using 1:2 ondex 1 ps 0 w lp title "RK2"