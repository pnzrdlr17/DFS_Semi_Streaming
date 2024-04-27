#!/bin/bash
# Usage ./dataGen.sh TYP N SP TST

TYP=$1  # 2 VARN 3 VARM 4 VARK
N=$2
SP=$3
TST=$4

if [ $TYP = '2' ]
then 
gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 1 #avgPass
gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 2 #maxPass
# gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 3 #avgHeight
# gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 4 #maxCompPerc
# gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 5 #numComp
# gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 6 #meanComp
# gnuplot -c plots/StrDFS_VarN.gp $N $SP $TST 7 #stdComp
elif [ $TYP = '3' ]
   then
   gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 1 #avgPass
   gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 2 #maxPass
   # gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 3 #avgHeight
   # gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 4 #maxCompPerc
   # gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 5 #numComp
   # gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 6 #meanComp
   # gnuplot -c plots/StrDFS_VarM.gp $N $SP $TST 7 #stdComp
   else 
   gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 1 #avgPass
   gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 2 #maxPass
   # gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 3 #avgHeight
   # gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 4 #maxCompPerc
   # gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 5 #numComp
   # gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 6 #meanComp
   # gnuplot -c plots/StrDFS_VarK.gp $N $SP $TST 7 #stdComp

   fi
 
