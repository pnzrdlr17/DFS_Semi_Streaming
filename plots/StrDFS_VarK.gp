reset
set terminal png size 640,540 enhanced font "arial,15"
#set terminal png size 700,600 enhanced font "arial,17"
N=ARG1
SP=ARG2
TST=ARG3
TYP=ARG4
location="./output/powlaw/"

if(TYP==1){
COL=2
LAB='Avg'
}
if(TYP==2){
COL=3
LAB='Max'
}
if(TYP==3){
COL=4
LAB='Height of DFS Tree'
}
if(TYP==4){
COL=5
LAB='Max Comp Size Perc'
}
if(TYP==5){
COL=6
LAB='No of Comp'
}
if(TYP==6){
COL=7
LAB='Mean Comp Size'
}
if(TYP==7){
COL=8
LAB='Std Dev Comp Size'
}

set output 'plots/powlaw/new/kpath_VarK_'.N.'_SP'.SP.'_'.LAB.'.png'

set multiplot

if(SP=='0')	M = '2n'
if(SP=='1')	M = '5n'
if(SP=='2')	M = 'nlog n'
if(SP=='3') 	M = 'n sqrt(n)'
if(SP=='4') 	M=  'n*n/2'

set   autoscale
set xlabel "Space Parameter k"
set xtics 200
#set xtics ("2" 200, "4" 400,  "6" 600, "8" 800, "10" 1000)


if(TYP==1||TYP==2){
set ylabel "Number of passes"
set yrange [0:10]
set ytics 0,1
}
if(TYP==3){
set ylabel "Height of DFS Tree"
set yrange [0:N]
set ytics 0,100
}
if(TYP==4){
set ylabel "Max Comp Size Perc"
set yrange [0:100]
set ytics 0,10
}
if(TYP==5){
set ylabel "No of Comp"
set yrange [0:20]
set ytics 0,2
}
if(TYP==6){
set ylabel "Mean Comp Size"
set yrange [0:N]
set ytics 0,100
}
if(TYP==7){
set ylabel "Std Dev Comp Size"
set yrange [0:N]
set ytics 0,100
}

#set xrange [9:]

#set format y "%2.0t{/Symbol \327}10^{%L}"
#set xtics 2500000
#set format y "10^{%L}"
#set format y "%7.0f"
set format x "%7.0f"
#set yrange [0:2500000]
#set ytics 0,1

set bmargin 5

if(TYP==1||TYP==2){
#set label center at graph 0.5,char 1 "".LAB.". Number of Passes vs Space Parameter k (Vertices ".N.")"font ",14"
}
if(TYP==3){
set label center at graph 0.5,char 1 " Height of DFS Tree vs Space Parameter k (Vertices ".N.")"font ",14"
}
if(TYP==4){
set label center at graph 0.5,char 1 " Max Comp Size Perc vs Space Parameter k (Vertices ".N.")"font ",14"
}
if(TYP==5){
set label center at graph 0.5,char 1 " No of Comp vs Space Parameter k (Vertices ".N.")"font ",14"
}
if(TYP==6){
set label center at graph 0.5,char 1 "Mean Comp Size vs Number of Edges (Vertices ".N.")"font ",14"
}
if(TYP==7){
set label center at graph 0.5,char 1 " Std Dev Comp Size vs Space Parameter k (Vertices ".N.")"font ",14"
}


set colors classic
set key out horiz
set key center top
set key samplen 2 spacing 1 width 1
set key box


# FOR RANDOM GRAPHS

#plot "".location."main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."previous/corrected/Klev_VarK_2.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_3.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_4.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
   #  "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
   #  "".location."latest/new/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

#plot "".location."/oldkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(1)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(1)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(2)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(3)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

# FOR POWERLAW GRAPHS

#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
 

plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \



if((TYP==1||TYP==2)&&1){
unset key
unset label
set size 0.5,0.6
set origin 0.45,0.3
#set title 'Zoom' offset 0,-2

set yrange [0:5]
set ytics 1
set xrange [0:40]
set xtics 10
set xlabel ""
set ylabel ""

# FOR RANDOM GRAPHS

#plot "".location."main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."previous/corrected/Klev_VarK_2.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_3.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_4.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
   #  "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
   #  "".location."latest/new/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

#plot "".location."/oldkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(1)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(1)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(2)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(3)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

# FOR POWERLAW GRAPHS

#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
 

plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \




#Another plot
if(1){
unset key
unset label
set size 0.38,0.6
set origin 0.14,0.3
#set title 'Zoom' offset 0,-2

set yrange [0:70]
set ytics 20
set xrange [0:5]
set xtics 2
set xlabel ""
set ylabel ""

# FOR RANDOM GRAPHS

#plot "".location."main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
  #   "".location."main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
  #   "".location."main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
  #   "".location."previous/corrected/Klev_VarK_2.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_3.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
   #  "".location."previous/corrected/Klev_VarK_4.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
   #  "".location."latest/corrected/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
   #  "".location."latest/new/KPath_VarK_4.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
   #  "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
   #  "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
   #  "".location."previous/corrected/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
   #  "".location."latest/new/klev_VarK_4.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

#plot "".location."/oldkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(1)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(1)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(2)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(2)' with linespoints, \
  #   "".location."/oldkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathO(3)' with linespoints, \
  #   "".location."/newkpath/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'KPathN(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(1)' with linespoints, \
   #  "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(1)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(2)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(2)' with linespoints, \
    #  "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPath(3)' with linespoints, \
    #  "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLev(3)' with linespoints, \


#plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \
  #   "".location."1000_old/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(3)' with linespoints, \
  #   "".location."1000_new/main_KPath_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(3)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(3)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_3_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(3)' with linespoints, \

# FOR POWERLAW GRAPHS

#plot "".location."latest/corrected/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_2.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
  #   "".location."latest/corrected/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
  #   "".location."latest/new/KPath_VarK_3.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \


#plot "".location."previous/corrected/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."latest/new/klev_VarK_2.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."previous/corrected/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."latest/new/klev_VarK_3.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \
 

plot "".location."1000_old/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(1)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(1)' with linespoints, \
   "".location."1000_old/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathO(2)' with linespoints, \
     "".location."1000_new/main_KPath_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kPathN(2)' with linespoints, \

#plot "".location."1000_old/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(1)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_1_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(1)' with linespoints, \
  #   "".location."1000_old/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevO(2)' with linespoints, \
  #   "".location."1000_new/main_KLev_VarK_".N."_2_".SP."_".TST."_S1.txt" using 1:(column(COL)) title 'kLevN(2)' with linespoints, \



}
}

unset multiplot

 


