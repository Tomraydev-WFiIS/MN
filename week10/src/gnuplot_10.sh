set terminal post enhanced colour solid font 25

f(x, y) = 5./2. * (x**2-y)**2 + (1-x)**2

set xrange [-2:2]
set yrange [-2:2]
set isosample 250, 250
set table 'mapa.dat'
splot f(x,y)
unset table
reset

set xrange [-2:2]
set yrange [-2:2]
set table "kontur.dat"
unset key
set contour
unset surface
set view map
set isosamples 100
set cntrparam levels 50
splot f(x,y) 
unset table

reset

set output "min1.eps"
set xlabel "x"
set ylabel "y"
set cblabel "f(x,y)" rotate by -90
set key top center outside horizontal
set grid
set xrange [-2:2]
set yrange [-2:2]
set xtics out
set ytics out
set size ratio -1
set palette rgbformulae 33,13,10
plot "mapa.dat" with image notitle, "out.dat" i 0 w lp lc rgb "orange" t "x_i, y_i", "kontur.dat" u 1:2 w l lt -1 notitle, "minimum.dat" u 1:2 w p pt 1 ps 3 lt 7 notitle

set output "min2.eps"
plot "mapa.dat" with image notitle, "out.dat" i 1 w lp lc rgb "orange" t "x_i, y_i", "kontur.dat" u 1:2 w l lt -1 notitle, "minimum.dat" u 1:2 w p pt 1 ps 3 lt 7 notitle
