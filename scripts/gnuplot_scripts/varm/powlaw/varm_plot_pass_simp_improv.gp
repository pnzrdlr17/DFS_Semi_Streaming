reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder=ARG1

set output "results/random/VARM/POWLAW/plot_kLev_pass_simp_improv.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Number of Edges (x10^5)"
set ylabel "Number of Pass(es)"

set xrange [100:400000]
set xtics ("1" 100000, "2" 200000, "3" 300000, "4" 400000)

set yrange [0:1050]
set ytics 0,200

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARM/POWLAW/".input_folder."/simp0.csv" using 1:4 with linespoints title "Simp0", \
    "results/random/VARM/POWLAW/".input_folder."/simp.csv" using 1:4 with linespoints title "Simp", \
    "results/random/VARM/POWLAW/".input_folder."/improv.csv" using 1:4 with linespoints title "Improv"

# Now let's set the zoomed-in plot
# unset key
# unset label

# set size 0.67,0.4
# set origin 0.3,0.48

# set xtics font "arial,15"
# set ytics font "arial,15"
# set xlabel ""
# set ylabel ""

# set xrange [100:10000]
# set xtics 0,2000

# set yrange [0:3.5]
# set ytics 0,1 

# # Zoomed-in plot
# plot "results/random/VARM/POWLAW/".input_folder."/kLev0(2).csv" using 1:4 with linespoints title "kLev0(2)", \
#     "results/random/VARM/POWLAW/".input_folder."/kLevN(2).csv" using 1:4 with linespoints title "kLevN(2)", \
#     "results/random/VARM/POWLAW/".input_folder."/kLev0(5).csv" using 1:4 with linespoints title "kLev0(5)", \
#     "results/random/VARM/POWLAW/".input_folder."/kLevN(5).csv" using 1:4 with linespoints title "kLevN(5)", \
#     "results/random/VARM/POWLAW/".input_folder."/kLev0(10).csv" using 1:4 with linespoints title "kLev0(10)", \
#     "results/random/VARM/POWLAW/".input_folder."/kLevN(10).csv" using 1:4 with linespoints title "kLevN(10)"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/varm/powlaw/varm_plot_pass_simp_improv.gp SimpImprov_N_1000_seed_1729_iter_10_20250723_062653