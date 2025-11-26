reset
set terminal png size 1000,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARN/UNIFORM/plot_sqrtN_memory.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Vertices"
set ylabel "Time (seconds)"

set xrange [0:10000]
set xtics 0,2000

set ylabel "Memory (MB)"
# set ytics 0,1

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARN/UNIFORM/".input_folder."/kpath_0.csv" using 1:($3/1024) with linespoints title "kPath0", \
    "results/random/VARN/UNIFORM/".input_folder."/kpath_N.csv" using 1:($3/1024) with linespoints title "kPathN", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_0.csv" using 1:($3/1024) with linespoints title "kLev0", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_N.csv" using 1:($3/1024) with linespoints title "kLevN"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.5,0.35
set origin 0.12,0.57

set xlabel ""
set ylabel ""

set xtics font "arial,15"
set ytics font "arial,15"

set xrange [0:3000]
set xtics 0,500

set yrange [2.5:5.5]       
set ytics 0,1

# Zoomed-in plot
plot "results/random/VARN/UNIFORM/".input_folder."/kpath_0.csv" using 1:($3/1024) with linespoints title "kPath0", \
    "results/random/VARN/UNIFORM/".input_folder."/kpath_N.csv" using 1:($3/1024) with linespoints title "kPathN", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_0.csv" using 1:($3/1024) with linespoints title "kLev0", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_N.csv" using 1:($3/1024) with linespoints title "kLevN"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varn/uniform/varn_plot_memory_sqrtn.gp sqrtN_seed_1729_itr_100_k_10_20250417_013751