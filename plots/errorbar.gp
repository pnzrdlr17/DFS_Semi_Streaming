reset
#set terminal png size 670,540 enhanced font "arial,15"
set terminal png size 1400,800 enhanced font "arial,23"
TYP=ARG1
location="./output/errorbar/"
if(TYP==1){
set output 'plots/errorbar/errorbarkpath_individual2.png'
} else {
set output 'plots/errorbar/errorbarklev_individual2.png'
}

set multiplot
set   autoscale

set xlabel "Space Parameter K"
set xrange [0:11]
set xtics 0,1

set ylabel "Number of Passes"
if(TYP==1){
    set yrange [0:900]
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

    
    fil="./output/errorbar/errorbarkpath_individual.txt"

    unique_x_values(file) = system("cut -d ' ' -f 1 '" . file . "' | sort -u")


    do for [x_value in unique_x_values(fil)] {

    plot fil using ($1 == x_value ? $1 : NaN):2:3 lc rgb "red" pt variable notitle with linespoints , \
         NaN with points lc rgb "red" pt 1 title 'kPathO',\
         NaN with points lc rgb "red" pt 4 title 'kPath1',\
         NaN with points lc rgb "red" pt 8 title 'kPath2',\
         NaN with points lc rgb "red" pt 3 title 'kPathN',\
    }

    #plot "".location."errorbarkpath.txt" using 1:2:3 with yerrorbars lc rgb "red" title "Improvement in KPath",

}else{

    fil="./output/errorbar/errorbarklev_individual.txt"

    unique_x_values(file) = system("cut -d ' ' -f 1 '" . file . "' | sort -u")


    do for [x_value in unique_x_values(fil)] {

    plot fil using ($1 == x_value ? $1 : NaN):2:3 lc rgb "blue" pt variable notitle with linespoints , \
         NaN with points lc rgb "blue" pt 1 title 'kLevO',\
         NaN with points lc rgb "blue" pt 4 title 'kLev1',\
         NaN with points lc rgb "blue" pt 8 title 'kLev2',\
         NaN with points lc rgb "blue" pt 3 title 'kLevN',\
    }


    #plot "".location."errorbarklev.txt" using 1:2:3 with yerrorbars lc rgb "blue" title "Improvement in KLev",
}

if(TYP==1 ){
    unset key
unset label
set size 0.65,0.75
set origin 0.3,0.15


set xtics 0,1
set yrange [0:10]
set ytics 0,1
set xlabel ""
set ylabel ""



fil="./output/errorbar/errorbarkpath_individual.txt"

unique_x_values(file) = system("cut -d ' ' -f 1 '" . file . "' | sort -u")


do for [x_value in unique_x_values(fil)] {

    plot fil using ($1 == x_value ? $1 : NaN):2:3 lc rgb "red" pt variable notitle with linespoints , \
         NaN with points lc rgb "red" pt 1 title 'kPathO',\
         NaN with points lc rgb "red" pt 4 title 'kPath1',\
         NaN with points lc rgb "red" pt 8 title 'kPath2',\
         NaN with points lc rgb "red" pt 3 title 'kPathN',\
}


#plot "".location."errorbarkpath.txt" using 1:2:3 with yerrorbars lc rgb "red" title "Improvement in KPath",

}
     
unset multiplot

 


