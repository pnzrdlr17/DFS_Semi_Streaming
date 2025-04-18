reset
set terminal png size 680,640 enhanced font "arial,15"
input_folder=ARG1
graph_type=ARG2
algorithm=ARG3

set output "results/random/VARM/".graph_type."/plot_".algorithm."_pass.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Edges"
set xrange [100:50000000]
set xtics 0,10000000

set ylabel "Number of Pass(es)"
# set yrange [0:200]
# set ytics 0,0.03

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(2).csv" using 1:4 with linespoints title "".algorithm."0(2)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(2).csv" using 1:4 with linespoints title "".algorithm."N(2)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(5).csv" using 1:4 with linespoints title "".algorithm."0(5)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(5).csv" using 1:4 with linespoints title "".algorithm."N(5)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(10).csv" using 1:4 with linespoints title "".algorithm."0(10)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(10).csv" using 1:4 with linespoints title "".algorithm."N(10)"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.65,0.41
# set origin 0.35,0.49 klev
set origin 0.3,0.39 #kpath
set xlabel font "arial,10"
set ylabel font "arial,10"
set xtics font "arial,10"
set ytics font "arial,10"
set xrange [100:250000]        # Zoomed range for X-axis
set xtics 0, 50000
# set yrange [0:10]        # Zoomed range for Y-axis
set ytics 1,2
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(2).csv" using 1:4 with linespoints title "".algorithm."0(2)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(2).csv" using 1:4 with linespoints title "".algorithm."N(2)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(5).csv" using 1:4 with linespoints title "".algorithm."0(5)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(5).csv" using 1:4 with linespoints title "".algorithm."N(5)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."0(10).csv" using 1:4 with linespoints title "".algorithm."0(10)", \
    "results/random/VARM/".graph_type."/".input_folder."/".algorithm."N(10).csv" using 1:4 with linespoints title "".algorithm."N(10)"

unset multiplot