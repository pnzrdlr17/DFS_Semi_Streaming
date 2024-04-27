LOC=$1 
GTYPE=$2
N=$3
M=$4

gnuplot -c plots/KPath_real.gp $LOC $GTYPE $N $M
gnuplot -c plots/KLev_real.gp $LOC $GTYPE $N $M









