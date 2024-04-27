reset
set terminal png size 640,540 enhanced font "arial,15"
TYP=ARG1
location="./output/errorbar/"
if(TYP==1){
set output 'plots/errorbar/errorbarkpath.png'
} else {
set output 'plots/errorbar/errorbarklev.png'
}

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:11]
set xtics 0,1

set ylabel "Number of Passes"
if(TYP==1){
    set yrange [0:1000]
    set ytics 0,100
} else{
    set yrange [0:10]
    set ytics 0,1
}


set bmargin 5

set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box


if(TYP==1){
    plot "".location."errorbarkpath.txt" using 1:2:3 with yerrorbars lc rgb "red" title "Improvement in KPath",
}else{
    plot "".location."errorbarklev.txt" using 1:2:3 with yerrorbars lc rgb "blue" title "Improvement in KLev",
}

if(TYP==1){
    unset key
unset label
set size 0.6,0.7
set origin 0.3,0.2


set xtics 0,1
set yrange [0:10]
set ytics 0,1
set xlabel ""
set ylabel ""

plot "".location."errorbarkpath.txt" using 1:2:3 with yerrorbars lc rgb "red" title "Improvement in KPath",

}
     
unset multiplot

 


