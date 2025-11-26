reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARN/POWLAW/plot_logN_time.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set ylabel "Time (seconds)"

set xrange [0:1000]
set xtics 0,200

set yrange [0:0.02]
# set ytics 0,200

set bmargin 3

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARN/POWLAW/".input_folder."/kpath_0.csv" using 1:2 with linespoints title "kPath0", \
    "results/random/VARN/POWLAW/".input_folder."/kpath_N.csv" using 1:2 with linespoints title "kPathN", \
    "results/random/VARN/POWLAW/".input_folder."/klev_0.csv" using 1:2 with linespoints title "kLev0", \
    "results/random/VARN/POWLAW/".input_folder."/klev_N.csv" using 1:2 with linespoints title "kLevN"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.45,0.54
set origin 0.15,0.32

set xlabel ""
set ylabel ""

set xtics font "arial,15"
set ytics font "arial,15"

set xrange [0:300]
set xtics 0,50

# set yrange [0:0.025]       
# set ytics 0,0.01

# plot "results/random/VARN/POWLAW/".input_folder."/kpath_0.csv" using 1:2 with linespoints title "kPath0", \
#     "results/random/VARN/POWLAW/".input_folder."/kpath_N.csv" using 1:2 with linespoints title "kPathN", \
#     "results/random/VARN/POWLAW/".input_folder."/klev_0.csv" using 1:2 with linespoints title "kLev0", \
#     "results/random/VARN/POWLAW/".input_folder."/klev_N.csv" using 1:2 with linespoints title "kLevN"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varn/powlaw/varn_plot_time_logn.gp logN_seed_1729_itr_1000_k_5_20250720_180236
#Usage: gnuplot -c scripts/gnuplot_scripts/varn/powlaw/varn_plot_time_logn.gp combined_logN_seed_1729_itr_1000_k_5_20250720_180236