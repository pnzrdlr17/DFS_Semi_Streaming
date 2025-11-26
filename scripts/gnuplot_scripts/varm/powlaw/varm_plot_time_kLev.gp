reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARM/POWLAW/plot_kLev_time.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Edges (x10^5)"
set ylabel "Time (seconds)"

set xrange [100:400000]
set xtics ("1" 100000, "2" 200000, "3" 300000, "4" 400000)

set yrange [0:0.9]
set ytics 0,0.2

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARM/POWLAW/".input_folder."/kLev0(2).csv" using 1:2 with linespoints title "kLev0(2)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(2).csv" using 1:2 with linespoints title "kLevN(2)", \
    "results/random/VARM/POWLAW/".input_folder."/kLev0(5).csv" using 1:2 with linespoints title "kLev0(5)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(5).csv" using 1:2 with linespoints title "kLevN(5)", \
    "results/random/VARM/POWLAW/".input_folder."/kLev0(10).csv" using 1:2 with linespoints title "kLev0(10)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(10).csv" using 1:2 with linespoints title "kLevN(10)"

# Now let's set the zoomed-in plot
unset key
unset label

set size 0.6,0.45
set origin 0.1,0.42

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel ""
set ylabel ""

set xrange [100:100000]
set xtics 0,20000

set yrange [0:0.15]
set ytics 0,0.05

# Zoomed-in plot
plot "results/random/VARM/POWLAW/".input_folder."/kLev0(2).csv" using 1:2 with linespoints title "kLev0(2)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(2).csv" using 1:2 with linespoints title "kLevN(2)", \
    "results/random/VARM/POWLAW/".input_folder."/kLev0(5).csv" using 1:2 with linespoints title "kLev0(5)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(5).csv" using 1:2 with linespoints title "kLevN(5)", \
    "results/random/VARM/POWLAW/".input_folder."/kLev0(10).csv" using 1:2 with linespoints title "kLev0(10)", \
    "results/random/VARM/POWLAW/".input_folder."/kLevN(10).csv" using 1:2 with linespoints title "kLevN(10)"
unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varm/powlaw/varm_plot_time_kLev.gp kLev_N_1000_seed_1729_iter_100_20250719_164040
#Usage: gnuplot -c scripts/gnuplot_scripts/varm/powlaw/varm_plot_time_kLev.gp kLev_N_1000_seed_1729_iter_1000_20250723_072020