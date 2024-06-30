reset
# -- Set plot environment --
set xrange [-1.6:0.6]
# -- Set font size --
set tics font ",18"
set xlabel "x(t)" font ",18"
set ylabel "y(t)" font ",18"
set key font ",18" spacing 1.2
set title "Kepler Orbit (e = 0.55)" font ",18"

plot  "Kepler.txt" using 2:3 pt 2 ps 0.8 lc rgb "blue" title "y(x)"