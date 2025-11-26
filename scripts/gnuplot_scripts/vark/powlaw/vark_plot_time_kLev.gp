reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder_logN=ARG1
input_folder_sqrtN=ARG2
input_folder_Nsq=ARG3

set output "results/random/VARK/POWLAW/plot_kLev_time.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Space Parameter K"
set ylabel "Time (seconds)"

set xrange [1:1000] 
set xtics 0,200

set yrange [0:2] 
set ytics 0,0.2

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/POWLAW/".input_folder_logN."/kLev0.csv" using 1:2 with linespoints title "kLev0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kLevN.csv" using 1:2 with linespoints title "kLevN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLev0.csv" using 1:2 with linespoints title "kLev0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLevN.csv" using 1:2 with linespoints title "kLevN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLev0.csv" using 1:2 with linespoints title "kLev0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLevN.csv" using 1:2 with linespoints title "kLevN(3)"

# Now let's set the zoomed-in plot
unset key
unset label

set xtics font "arial,15"
set ytics font "arial,15"

set size 0.6,0.5
set origin 0.2,0.36

set xlabel ""
set ylabel ""

set xrange [1:200] #kPath        # Zoomed range for X-axis
set xtics 0,20
set yrange [0:0.05] #kPath        # Zoomed range for Y-axis
set ytics 0,0.01 #kPath


plot "results/random/VARK/POWLAW/".input_folder_logN."/kLev0.csv" using 1:2 with linespoints title "kLev0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kLevN.csv" using 1:2 with linespoints title "kLevN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLev0.csv" using 1:2 with linespoints title "kLev0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLevN.csv" using 1:2 with linespoints title "kLevN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLev0.csv" using 1:2 with linespoints title "kLev0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLevN.csv" using 1:2 with linespoints title "kLevN(3)"

unset multiplot

#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_time_kLev.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250721_051734 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250721_051713 sparsity_N2_N_1000_seed_1729_iter_100_20250719_164310
#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_time_kLev.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_N2_N_1000_seed_1729_iter_100_20250722_999999