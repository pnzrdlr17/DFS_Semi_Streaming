reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARM/UNIFORM/plot_kLev_memory.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Edges (x10^7)"
set ylabel "Memory (MB)"

set xrange [100:50000000]
set xtics ("1" 10000000, "2" 20000000, "3" 30000000, "4" 40000000, "5" 50000000)

set yrange [0:80]
set ytics 0,20

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARM/UNIFORM/".input_folder."/kLev0(2).csv" using 1:($3/1024) with linespoints title "kLev0(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(2).csv" using 1:($3/1024) with linespoints title "kLevN(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLev0(5).csv" using 1:($3/1024) with linespoints title "kLev0(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(5).csv" using 1:($3/1024) with linespoints title "kLevN(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLev0(10).csv" using 1:($3/1024) with linespoints title "kLev0(10)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(10).csv" using 1:($3/1024) with linespoints title "kLevN(10)"

# Now let's set the zoomed-in plot
unset key
unset label

set size 0.75,0.5
set origin 0.2,0.35

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel font "arial,15"
set xlabel "Number of Edges (x10^5)" offset 0,0.75
set ylabel ""

set xrange [100:400000]
set xtics ("1" 100000, "2" 200000, "3" 300000, "4" 400000)

set yrange [0:100]
# set ytics 0,0.1 

# Zoomed-in plot
plot "results/random/VARM/UNIFORM/".input_folder."/kLev0(2).csv" using 1:($3/1024) with linespoints title "kLev0(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(2).csv" using 1:($3/1024) with linespoints title "kLevN(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLev0(5).csv" using 1:($3/1024) with linespoints title "kLev0(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(5).csv" using 1:($3/1024) with linespoints title "kLevN(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLev0(10).csv" using 1:($3/1024) with linespoints title "kLev0(10)", \
    "results/random/VARM/UNIFORM/".input_folder."/kLevN(10).csv" using 1:($3/1024) with linespoints title "kLevN(10)"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varm/uniform/varm_plot_memory_kLev.gp kLev_N_10000_seed_1729_iter_100_20250422_239999      