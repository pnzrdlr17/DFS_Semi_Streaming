reset
set terminal png size 680,640 enhanced font "arial,15"
input_folder=ARG1
graph_type=ARG2
sparsity=ARG3

set output "results/random/VARN/".graph_type."/plot_".sparsity."_time.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set xtics 0,2000
# set xtics 0,10000000

set ylabel "Time (seconds)"
# set yrange [0:200]
# set ytics 0,0.03

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARN/".graph_type."/".input_folder."/kpath_0.csv" using 1:2 with linespoints title "kPath0", \
    "results/random/VARN/".graph_type."/".input_folder."/kpath_N.csv" using 1:2 with linespoints title "kPathN", \
    "results/random/VARN/".graph_type."/".input_folder."/klev_0.csv" using 1:2 with linespoints title "kLev0", \
    "results/random/VARN/".graph_type."/".input_folder."/klev_N.csv" using 1:2 with linespoints title "kLevN"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.62,0.41
# set origin 0.35,0.49 klev
set origin 0.1,0.49 #kpath
set xlabel font "arial,10"
set ylabel font "arial,10"
set xtics font "arial,10"
set ytics font "arial,10"
set xrange [100:2000]        # Zoomed range for X-axis
set xtics 0, 500
# set yrange [0:10]        # Zoomed range for Y-axis
# set ytics 1,2
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/VARN/".graph_type."/".input_folder."/kpath_0.csv" using 1:2 with linespoints title "kPath0", \
    "results/random/VARN/".graph_type."/".input_folder."/kpath_N.csv" using 1:2 with linespoints title "kPathN", \
    "results/random/VARN/".graph_type."/".input_folder."/klev_0.csv" using 1:2 with linespoints title "kLev0", \
    "results/random/VARN/".graph_type."/".input_folder."/klev_N.csv" using 1:2 with linespoints title "kLevN"

unset multiplot