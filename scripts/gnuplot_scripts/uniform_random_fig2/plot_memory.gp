reset
set terminal png size 680,640 enhanced font "arial,25"
sparsity=ARG1

set output 'results/random/uniform_figure_2/plot_'.sparsity.'/varn_memory.png'

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set xrange [10:10000]
set xtics 0,2000

set ylabel "Memory (MB)"
set yrange [3:18]
set ytics 3,3

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

# Full plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:3 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:3 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:3 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:3 with linespoints title 'kLevN'


unset key
unset label
set size 0.6,0.475
set origin 0.14,0.4
set xlabel font "arial,15"
set ylabel font "arial,15"
set xtics font "arial,15"
set ytics font "arial,15"
set xrange [0:1000]        # Zoomed range for X-axis
set xtics 0, 300
set yrange [3.5:5.5]        # Zoomed range for Y-axis
set ytics 4,1
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:3 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:3 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:3 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:3 with linespoints title 'kLevN'

unset multiplot