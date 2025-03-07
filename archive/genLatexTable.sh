#!/bin/bash
dataSetS=(Belcastro ArxAP BrightK)
dataNS=()
dataMS=()
dataSetM=(Twitch Gowalla Amazon)
dataNM=()
dataMM=()
dataSetL=(RoadnetPA RoadnetCA Orkut LiveJournal DBLP)
dataNL=()
dataML=()
algo=(kpath klev)
hnum=(0 1 2 3)
heuristics=(0 1 2 N)
space=(1 2 5 10 C)
IFS=','

for data in ${dataSetS[@]}
do
	echo -n "${data} & "
	for hu in ${hnum[@]}
	do
		echo -n "H${hu} & "
		for alg in ${algo[@]};
		do
			for sp in ${space[@]};
			do
				file=${data}_${algo}_${heuristics[hu]}_${sp}.txt
				if [ ! -f ${file} ]; then
					echo -n " - & "
				else
	                          	read time mem pass < ${file}
				  	# Time
					# echo -n " ${time} & "

					# Memory
					mem_mb=$(echo "scale=2; ${mem}/1024" | bc)
                    echo -n " ${mem_mb} & "
					
					# Pass
					# echo -n " ${pass} & "
				fi
                    	done
		done
		echo -n " \\ "
	done
	echo " \hline "	
done

