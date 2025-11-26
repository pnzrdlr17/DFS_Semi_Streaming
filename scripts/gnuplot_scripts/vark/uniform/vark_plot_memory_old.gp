reset
set terminal png size 680,640 enhanced font "arial,15"
graph_type=ARG1
algorithm=ARG2
input_folder_logN=ARG3
input_folder_sqrtN=ARG4
# input_folder_Nsq=ARG5

set output "results/random/VARK/".graph_type."/plot_".algorithm."_memory.png"

set datafile separator ","

set multiplot
set   autoscale

set xlabel "Space Parameter K"
# set xrange [100:50000000]
set xtics 0,2000

set ylabel "Memory (MB)"
set yrange [0:200]
# set ytics 0,0.03

set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box

plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(3)", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(3)"

# Now let's set the zoomed-in plot
unset key
unset label
set size 0.67,0.45
# set origin 0.35,0.49 klev
set origin 0.25,0.44 #kpath
set xlabel font "arial,10"
set ylabel font "arial,10"
set xtics font "arial,10"
set ytics font "arial,10"
set xrange [1:100]        # Zoomed range for X-axis
set xtics 0, 25
set yrange [0:120]        # Zoomed range for Y-axis
# set ytics 1,2
set xlabel ""
set ylabel ""

# Zoomed-in plot
plot "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(1)", \
    "results/random/VARK/".graph_type."/".input_folder_logN."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(1)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(2)", \
    "results/random/VARK/".graph_type."/".input_folder_sqrtN."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(2)"
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."0.csv" using 1:($3/1024) with linespoints title "".algorithm."0(3)", \
    # "results/random/VARK/".graph_type."/".input_folder_Nsq."/".algorithm."N.csv" using 1:($3/1024) with linespoints title "".algorithm."N(3)"

unset multiplot