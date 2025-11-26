reset
set terminal png size 1050,700 enhanced font "arial,26"
input_folder_logN=ARG1
input_folder_sqrtN=ARG2
input_folder_Nsq=ARG3

set output "results/random/VARK/UNIFORM/plot_kLev_memory.png"

set datafile separator ","

set multiplot
set autoscale

set xlabel "Space Parameter K"
set ylabel "Memory (MB)"

set xrange [0:500] 
set xtics 0,50

set yrange [0:240]
set ytics 0,50

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/UNIFORM/".input_folder_logN."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(1)", \
    "results/random/VARK/UNIFORM/".input_folder_logN."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(1)", \
    "results/random/VARK/UNIFORM/".input_folder_sqrtN."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(2)", \
    "results/random/VARK/UNIFORM/".input_folder_sqrtN."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(2)", \
    "results/random/VARK/UNIFORM/".input_folder_Nsq."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(3)", \
    "results/random/VARK/UNIFORM/".input_folder_Nsq."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(3)"

# Now let's set the zoomed-in plot
unset key
unset label

set size 0.5,0.4
set origin 0.1,0.45

set xtics font "arial,15"
set ytics font "arial,15"
set xlabel ""
set ylabel ""

set xrange [1:10000]
set xtics 0,2000 

set yrange [0:2000] 
set ytics 0,1000 

# Zoomed-in plot
plot "results/random/VARK/UNIFORM/".input_folder_logN."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(1)", \
    "results/random/VARK/UNIFORM/".input_folder_logN."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(1)", \
    "results/random/VARK/UNIFORM/".input_folder_sqrtN."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(2)", \
    "results/random/VARK/UNIFORM/".input_folder_sqrtN."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(2)", \
    "results/random/VARK/UNIFORM/".input_folder_Nsq."/kLev0.csv" using 1:($3/1024) with linespoints title "kLev0(3)", \
    "results/random/VARK/UNIFORM/".input_folder_Nsq."/kLevN.csv" using 1:($3/1024) with linespoints title "kLevN(3)"

unset multiplot

#Usage: gnuplot -c scripts/gnuplot_scripts/vark/uniform/vark_plot_memory_kLev.gp sparsity_logN_N_10000_seed_1729_iter_100_20250418_030447 sparsity_sqrtN_N_10000_seed_1729_iter_100_20250418_030503 sparsity_N2_N_10000_seed_1729_iter_10_20250419_023547