reset
# -- Set plot environment --
# -- Set font size --
set tics font ",18"
set xlabel "t" font ",18"
set ylabel "E(t)" font ",18"
set key font ",18" spacing 1.2
set title "Energy" font ",18"

plot "kepler.txt" using 1:6 ps 0 w lp title "Ek"
replot "kepler.txt" using 1:7 ps 0 w lp title "Ep"
replot "kepler.txt" using 1:8 ps 0 w lp title "Etot"
