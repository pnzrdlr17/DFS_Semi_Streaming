reset
set terminal png size 1000,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARN/UNIFORM/plot_logN_pass_kLev.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Number of Vertices"
set ylabel "Number of Pass(es)"

set xrange [0:10000]
set xtics 0,2000

set yrange [0.5:7]
set ytics 0,1

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARN/UNIFORM/".input_folder."/klev_0.csv" using 1:4 with linespoints title "kLev0", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_1.csv" using 1:4 with linespoints title "kLev1", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_2.csv" using 1:4 with linespoints title "kLev2", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_N.csv" using 1:4 with linespoints title "kLevN"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.4,0.45
set origin 0.38,0.47

set xlabel ""
set ylabel ""

set xtics font "arial,15"
set ytics font "arial,15"

set xrange [760:1500]
set xtics 0,250
set xtics add("800" 800)

set yrange [0.5:4.5]       
set ytics 0,1

# Zoomed-in plot
plot "results/random/VARN/UNIFORM/".input_folder."/klev_0.csv" using 1:4 with linespoints title "kLev0", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_1.csv" using 1:4 with linespoints title "kLev1", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_2.csv" using 1:4 with linespoints title "kLev2", \
    "results/random/VARN/UNIFORM/".input_folder."/klev_N.csv" using 1:4 with linespoints title "kLevN"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varn/uniform/varn_plot_pass_logn_kLev.gp logN_kLev_seed_1729_itr_100_k_10_20250723_175731