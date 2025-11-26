reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARN/POWLAW/plot_sqrtN_pass_combined.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Vertices"
set ylabel "Number of Pass(es)"

set xrange [0:1000]
set xtics 0,200

set yrange [0:1050]
set ytics 0,200

set bmargin 4

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARN/POWLAW/".input_folder."/simp0.csv" using 1:4 with linespoints title "Simp0", \
    "results/random/VARN/POWLAW/".input_folder."/simp.csv" using 1:4 with linespoints title "Simp", \
    "results/random/VARN/POWLAW/".input_folder."/improv.csv" using 1:4 with linespoints title "Improv", \
    "results/random/VARN/POWLAW/".input_folder."/kpath_0.csv" using 1:4 with linespoints title "kPath0", \
    "results/random/VARN/POWLAW/".input_folder."/kpath_N.csv" using 1:4 with linespoints title "kPathN", \
    "results/random/VARN/POWLAW/".input_folder."/klev_0.csv" using 1:4 with linespoints title "kLev0", \
    "results/random/VARN/POWLAW/".input_folder."/klev_N.csv" using 1:4 with linespoints title "kLevN"

# Now let's set the zoomed-in plot
unset key
unset label

set size 0.52,0.47
set origin 0.14,0.4

set xtics font "arial,15"
set ytics font "arial,15"

set xlabel ""
set ylabel ""

set xrange [10:1000]     
# set xtics 0,20,100
# set xtics add("150" 150, "200" 200)      

set yrange [0:8] 
set ytics 0,2

# Zoomed-in plot
plot "results/random/VARN/POWLAW/".input_folder."/simp0.csv" using 1:4 with linespoints title "Simp0", \
    "results/random/VARN/POWLAW/".input_folder."/simp.csv" using 1:4 with linespoints title "Simp", \
    "results/random/VARN/POWLAW/".input_folder."/improv.csv" using 1:4 with linespoints title "Improv", \
    "results/random/VARN/POWLAW/".input_folder."/kpath_0.csv" using 1:4 with linespoints title "kPath0", \
    "results/random/VARN/POWLAW/".input_folder."/kpath_N.csv" using 1:4 with linespoints title "kPathN", \
    "results/random/VARN/POWLAW/".input_folder."/klev_0.csv" using 1:4 with linespoints title "kLev0", \
    "results/random/VARN/POWLAW/".input_folder."/klev_N.csv" using 1:4 with linespoints title "kLevN"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varn/powlaw/varn_plot_pass_sqrtn.gp combined_sqrtN_seed_1729_itr_100_20250723_180102