reset
# -- Set plot environment --
set term cairolatex pdf
set output "pendulum.tex"
# -- Set font size --
set tics font ",18"
set xlabel "$\theta$" font ",18"
set ylabel "$v$" font ",18"
set key font ",18" spacing 1.2
set title "$Trajectory v(\theta)$" font ",18"

plot "pendulum.txt" using 1:2 index 1 ps 0 w lp title "$RK2$"
replot "pendulum.txt" using 1:2 index 0 ps 0 w lp title "$Position-Verlet$"
