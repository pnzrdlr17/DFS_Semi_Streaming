reset
set terminal png size 680,640 enhanced font "arial,25"
sparsity=ARG1

set output 'results/random/uniform_figure_2/plot_'.sparsity.'/varn_pass.png'

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set xrange [10:10000]
set xtics 0,2000

set ylabel "Number of Passes"
set yrange [0:10]
set ytics 0,2

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

# Full plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:4 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:4 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:4 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:4 with linespoints title 'kLevN'

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.75,0.475
set origin 0.225,0.375

set xrange [0:250]        # Zoomed range for X-axis
set xtics 0,100
set yrange [0:4]        # Zoomed range for Y-axis
#set ytics 0,50
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:4 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:4 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:4 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:4 with linespoints title 'kLevN'

unset multiplot