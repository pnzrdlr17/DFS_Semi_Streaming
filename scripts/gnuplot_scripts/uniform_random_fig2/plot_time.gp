reset
set terminal png size 680,640 enhanced font "arial,25"
sparsity=ARG1

set output 'results/random/uniform_figure_2/plot_'.sparsity.'/varn_time.png'

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set xrange [10:10000]
set xtics 0,2000

set ylabel "Time (seconds)"
set yrange [0:0.2]
set ytics 0,0.03

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

# Full plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:2 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:2 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:2 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:2 with linespoints title 'kLevN'

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.67,0.475
set origin 0.15,0.38
set xlabel font "arial,15"
set ylabel font "arial,15"
set xtics font "arial,15"
set ytics font "arial,15"
set xrange [0:2000]        # Zoomed range for X-axis
set xtics ("0" 0, "500" 500, "1K" 1000, "1.5K" 1500, "2K" 2000)
set yrange [0:0.025]        # Zoomed range for Y-axis
set ytics 0,0.01
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/uniform_figure_2/plot_".sparsity."/kpath_0.csv" using 1:2 with linespoints title 'kPathO', \
    "results/random/uniform_figure_2/plot_".sparsity."/kpath_N.csv" using 1:2 with linespoints title 'kPathN', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_0.csv" using 1:2 with linespoints title 'kLevO', \
    "results/random/uniform_figure_2/plot_".sparsity."/klev_N.csv" using 1:2 with linespoints title 'kLevN'

unset multiplot