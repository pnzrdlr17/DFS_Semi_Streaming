reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARM/UNIFORM/plot_kPath_time.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Edges (x10^7)"
set ylabel "Time (seconds)"

set xrange [100:50000000]
set xtics ("1" 10000000, "2" 20000000, "3" 30000000, "4" 40000000, "5" 50000000)

# set yrange [0:300]
# set ytics 0,50

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARM/UNIFORM/".input_folder."/kPath0(2).csv" using 1:2 with linespoints title "kPath0(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(2).csv" using 1:2 with linespoints title "kPathN(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPath0(5).csv" using 1:2 with linespoints title "kPath0(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(5).csv" using 1:2 with linespoints title "kPathN(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPath0(10).csv" using 1:2 with linespoints title "kPath0(10)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(10).csv" using 1:2 with linespoints title "kPathN(10)"

# Now let's set the zoomed-in plot
unset key
unset label

set size 0.61,0.43
set origin 0.1,0.43

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel font "arial,15"
set xlabel "Number of Edges (x10^4)" offset 0,0.75
set ylabel ""

set xrange [100:75000]
set xtics ("1" 10000, "2" 20000, "3" 30000, "4" 40000, "5" 50000, "6" 60000, "7" 70000, "8" 80000, "9" 90000)

set yrange [0:0.4]
set ytics 0,0.1 

# Zoomed-in plot
plot "results/random/VARM/UNIFORM/".input_folder."/kPath0(2).csv" using 1:2 with linespoints title "kPath0(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(2).csv" using 1:2 with linespoints title "kPathN(2)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPath0(5).csv" using 1:2 with linespoints title "kPath0(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(5).csv" using 1:2 with linespoints title "kPathN(5)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPath0(10).csv" using 1:2 with linespoints title "kPath0(10)", \
    "results/random/VARM/UNIFORM/".input_folder."/kPathN(10).csv" using 1:2 with linespoints title "kPathN(10)"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varm/uniform/varm_plot_time_kPath.gp kPath_N_10000_seed_1729_iter100_20250422_239999      