reset
set terminal png size 640,540 enhanced font "arial,15"

set output 'plots/errorbar/check.png'

set multiplot
set   autoscale

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

set xrange [0:2]
set xtics 0,0.5

set yrange [0:70]
set ytics 0,10

# Set labels for axes
set xlabel "Space Parameter (k)"
set ylabel "Improvement in No of Passes"


fil="./plots/check.txt"

unique_x_values(file) = system("cut -d ' ' -f 1 '" . file . "' | sort -u")


do for [x_value in unique_x_values(fil)] {

plot fil using ($1 == x_value ? $1 : NaN):2:3 lc rgb "blue" pt variable notitle with linespoints , \

}

