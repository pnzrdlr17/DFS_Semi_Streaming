reset
set terminal png size 680,640 enhanced font "arial,25"
location=ARG1
GType=ARG2
N=ARG3
M=ARG4

set output 'plots/real/'.GType.'/klev_n.png'

set   autoscale

set xlabel "Space Parameter K"
set xrange [0:11]
set xtics 0,1

set ylabel "Number of Passes"
set yrange [0:10]
set ytics 0,1

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box


plot "".location."klev_plot_data.txt" using 1:(column(2)) title 'kLevO' with linespoints, \
    "".location."klev_plot_data.txt" using 1:(column(3)) title 'kLev1' with linespoints,\
     "".location."klev_plot_data.txt" using 1:(column(4)) title 'kLev2' with linespoints, \
     "".location."klev_plot_data.txt" using 1:(column(5)) title 'kLevN' with linespoints, \


#plot "".location."klev_plot_data.txt" using 1:(column(2)) title 'kLevO' with linespoints, \
  #   "".location."klev_plot_data.txt" using 1:(column(5)) title 'kLevN' with linespoints lc rgb "blue",

unset multiplot

 


