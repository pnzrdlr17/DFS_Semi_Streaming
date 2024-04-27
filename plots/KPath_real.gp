reset
set terminal png size 640,540 enhanced font "arial,15"
location=ARG1
GType=ARG2
N=ARG3
M=ARG4

set output 'plots/real/'.GType.'/kpath.png'

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:11]
set xtics 0,1

set ylabel "Number of Passes"
set yrange [0:350]
set ytics 0,35


set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box


#plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'B1' with linespoints, \
#    "".location."kpath_plot_data.txt" using 1:(column(3)) title 'B1+H1' with linespoints,\
#    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'B1+H1+H2' with linespoints,

plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'KPathO' with linespoints, \
    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'KPathN' with linespoints lc rgb "blue",



unset key
unset label
set size 0.6,0.7
set origin 0.3,0.2


set xtics 0,1
set yrange [0:20]
set ytics 0,2
set xlabel ""
set ylabel ""

#plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'B1' with linespoints, \
#    "".location."kpath_plot_data.txt" using 1:(column(3)) title 'B1+H1' with linespoints,\
#    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'B1+H1+H2' with linespoints,

plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'KPathO' with linespoints, \
    "".location."kpath_plot_data.txt" using 1:(column(4))  title 'KPathN' with linespoints lc rgb "blue",
unset multiplot

 


