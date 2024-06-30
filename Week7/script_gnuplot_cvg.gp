reset
# -- Set plot environment --
set log x
set log y
set xrange[0.001:10]
# -- Set font size --
set tics font ",18"
set xlabel "dt" font ",18"
set ylabel "error" font ",18"
set key font ",18" spacing 1.2
set title font ",18"

Euler = "cvg_euler.txt"
RK2 = "cvg_RK2.txt"
RK4 = "cvg_RK4.txt"

plot  Euler using 1:2
replot RK2 using 1:2
replot RK4 using 1:2