reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder_logN=ARG1
input_folder_sqrtN=ARG2
input_folder_Nsq=ARG3

set output "results/random/VARK/POWLAW/plot_kLev_pass.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Space Parameter K"
set ylabel "Number of Pass(es)"

set xrange [1:100] 
set xtics 0,20 

set yrange [0:8] #kLev
set ytics 0,1 #kLev

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/POWLAW/".input_folder_logN."/kLev0.csv" using 1:4 with linespoints title "kLev0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kLevN.csv" using 1:4 with linespoints title "kLevN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLev0.csv" using 1:4 with linespoints title "kLev0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLevN.csv" using 1:4 with linespoints title "kLevN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLev0.csv" using 1:4 with linespoints title "kLev0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLevN.csv" using 1:4 with linespoints title "kLevN(3)"

unset key
unset label

set size 0.57,0.44
set origin 0.38,0.42

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel ""
set ylabel ""


set xrange [1:1000] 
set xtics 0,250 
set yrange [0:4.5] 
set ytics 0,1

# Zoomed-in plot
plot "results/random/VARK/POWLAW/".input_folder_logN."/kLev0.csv" using 1:4 with linespoints title "kLev0(1)", \
    "results/random/VARK/POWLAW/".input_folder_logN."/kLevN.csv" using 1:4 with linespoints title "kLevN(1)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLev0.csv" using 1:4 with linespoints title "kLev0(2)", \
    "results/random/VARK/POWLAW/".input_folder_sqrtN."/kLevN.csv" using 1:4 with linespoints title "kLevN(2)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLev0.csv" using 1:4 with linespoints title "kLev0(3)", \
    "results/random/VARK/POWLAW/".input_folder_Nsq."/kLevN.csv" using 1:4 with linespoints title "kLevN(3)"

unset multiplot

#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_pass_kLev.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250721_051734 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250721_051713 sparsity_N2_N_1000_seed_1729_iter_100_20250719_164310
#Usage:  gnuplot -c scripts/gnuplot_scripts/vark/powlaw/vark_plot_pass_kLev.gp sparsity_logN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_sqrtN_N_1000_seed_1729_iter_1000_20250722_999999 sparsity_N2_N_1000_seed_1729_iter_100_20250722_999999
