reset
# -- Set plot environment --
# -- Set font size --
set tics font ",18"
set xlabel "E" font ",18"
set ylabel "f(E)" font ",18"
set key font ",18" spacing 1.2
set title "f(E) (e=0.55; t=0.5; T=1)" font ",18"

plot  2*pi*0.5 + 0.55*sin(x) - x title "f(E)"