reset
set terminal png size 680,640 enhanced font "arial,25"
location=ARG1
GType=ARG2
N=ARG3
M=ARG4

set output 'plots/real/'.GType.'/kpath_n.png'

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


plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'kPathO' with linespoints, \
   "".location."kpath_plot_data.txt" using 1:(column(3)) title 'kPath1' with linespoints,\
    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'kPath2' with linespoints,\
   "".location."kpath_plot_data.txt" using 1:(column(5)) title 'kPathN' with linespoints,

#plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'kPathO' with linespoints, \
  #  "".location."kpath_plot_data.txt" using 1:(column(5)) title 'kPathN' with linespoints lc rgb "blue",



unset key
unset label
set size 0.7,0.6
set origin 0.27,0.25

set xrange [0:10]
set xtics 0,1
set yrange [0:10]
set ytics 0,2
set xlabel ""
set ylabel ""

plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'kPathO' with linespoints, \
   "".location."kpath_plot_data.txt" using 1:(column(3)) title 'kPath1' with linespoints,\
    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'kPath2' with linespoints,\
   "".location."kpath_plot_data.txt" using 1:(column(5)) title 'kPathN' with linespoints,

#plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'kPathO' with linespoints, \
  #  "".location."kpath_plot_data.txt" using 1:(column(5)) title 'kPathN' with linespoints lc rgb "blue",


unset multiplot

 


