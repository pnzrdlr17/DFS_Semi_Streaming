
FOR CU:
./dataGen.sh 1 49 107 ./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa ./output/real/CU


For Mpdz:
./dataGen.sh 1 212 244 ./input/Mpdz/download.tsv.maayan-pdzbase/maayan-pdzbase/out.maayan-pdzbase  ./output/real/Mpdz


FOR AJazz:
./dataGen.sh 1 198 2742 ./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz  ./output/real/AJazz

For CH:
Dataset not available

For HM:
./dataGen.sh 1 2426 16631 ./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster  ./output/real/HM


For Apgp:
Dataset not available

For ArxAP:
./dataGen.sh 1 18771 198050 ./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh  ./output/real/ArxAP


For AsCaida:
./dataGen.sh 1 26475 53381 ./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105/out.as-caida20071105 ./output/real/AsCaida


For BrightK:
./dataGen.sh 1 58228 214078 ./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges ./output/real/BrightK


For LMocha:
./dataGen.sh 1 104103 2193083 ./input/LMocha/download.tsv.livemocha/livemocha/out.livemocha ./output/real/LMocha


For FlickrE:
./dataGen.sh 1 105938 2316948 ./input/FlickrE/download.tsv.flickrEdges/flickrEdges/out.flickrEdges ./output/real/FlickrE


For WordNet:
./dataGen.sh 1 146005 656999 ./input/WordNet/download.tsv.wordnet-words/wordnet-words/out.wordnet-words ./output/real/WordNet


For Douban: -> from here we are not running simp algorithm
./dataGen.sh 1 154908 327162 ./input/Douban/download.tsv.douban/douban/out.douban ./output/real/Douban


For Gowalla:
./dataGen.sh 1 196591 950327 ./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges ./output/real/Gowalla


For Dblp:
./dataGen.sh 1 317080 1049866 ./input/Dblp/download.tsv.com-dblp/com-dblp/out.com-dblp ./output/real/Dblp


For  Amazon:
./dataGen.sh 1 334863 925872 ./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon  ./output/real/Amazon


For REAL:
./dataGen.sh 1 5 5 ./input/Real/dataset.txt  ./output/real/Real













// to console a statement use cerr << "statement" << endl -> instead of writing to the file


Run this command in case of shell script command not found errors:
sed -i -e 's/\r$//' plot.sh






KPath with heursitic
CU   & 49    & 107 &   2.18 & 5 & 2& 2& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 16 & 9& 7& 5& 4& 3& 3& 2& 2& 2 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 14 &7& 4& 4& 3& 3& 3& 1& 1& 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 35 &19& 12& 9& 4& 6& 3& 3& 2& 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 9& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 13& 4& 3& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 22& 9& 6& 5& 4& 4 &3& 3& 3& 2\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 35& 15& 11& 6& 5& 4& 5& 3& 3& 3 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 67& 18& 4& 3& 3& 1& 1& 1& 1& 1\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 7& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 28& 6& 5& 2& 2& 1& 1& 1& 1& 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 47& 14& 6& 5& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 100& 7& 4& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]




KLev with heursitic

CU   & 49    & 107 &   2.18 & 3& 3& 3& 3& 3& 3& 3& 3& 3& 2\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 2& 2& 2& 2& 2& 2& 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 4 &4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4 \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 3& 3& 3& 3& 3& 3& 3& 3& 3& 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 5& 5& 5& 5& 5& 5& 5& 5& 6& 5\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 3& 3& 3& 3& 3& 3& 3& 3& 3& 3\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 5 &5& 5& 5& 5& 5& 5& 5& 5& 5\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 4& 4& 4& 4& 4& 4& 4& 5& 5& 5 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 &  5& 5& 5& 5& 5& 5& 5& 5& 5& 5\\[0.1cm]



KPath with heursitic and randomization
CU   & 49    & 107 &   2.18 & 5 & 2& 2& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 12 & 9& 6& 5& 4& 3& 2& 2& 2& 2 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 15 &7& 4& 3& 2& 3& 2& 1& 1& 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 34 &15& 10& 6& 5& 3& 3& 2& 2& 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 9& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 14& 4& 3& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 19& 8& 6& 4& 4& 3 &3& 3& 2& 2\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 26& 11& 7& 6& 4& 3& 3& 3& 3& 2 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 64& 19& 4& 3& 3& 1& 1& 1& 1& 1\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 7& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 23& 5& 3& 2& 3& 1& 1& 1& 1& 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 38& 10& 5& 5& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 93& 7& 4& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]



KPath without heursitic
CU   & 49    & 107 &   2.18 & 4 & 3 & 2 & 2 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 16 & 10 & 5 & 3 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 13 & 8 & 4 & 2 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 33 & 17 & 6 & 4\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 8 & 3 & 2 & 2\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 14 & 6 & 2 & 2\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 22 & 9 & 5 & 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 43 & 18 & 6 & 4 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 66 & 19 & 2 & 2\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 7 & 3 & 2 & 2\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 32 & 6 & 2 & 2\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 43& 13& 2& 2\\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 107& 8& 2& 2\\[0.1cm]




ulimit -s 4194304

./dataGen.sh 1 49 107 - Real
./dataGen.sh 2 1000 2 10  - VARN
./dataGen.sh 3 1000 4 10  - VARM - till n*2
./dataGen.sh 3 1000 3 10  - VARM - till nsqrt(n)
./dataGen.sh 4 1000 2 10  - VARK


KPath without one pass heursitic and corrected nk space + with duplicates
CU   & 49    & 107 &   2.18 & 5 & 4& 3& 2& 2& 2& 2& 2& 2& 2 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 19 & 16& 10& 7& 5& 5& 4& 3& 3& 3 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 47 & 13& 8& 5& 5& 4& 4& 4& 3& 2 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 231 & 33& 17& 12& 10& 6& 7& 3& 3& 3\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 43& 8& 3& 2& 2& 2& 2& 2& 2& 2\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 242& 14& 6& 4& 2& 2& 2& 2& 2& 2\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 850& 22& 9& 7& 6& 5 &4& 4& 4& 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 737& 43& 18& 10& 7& 6& 5& 5& 4& 4 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 303& 66& 19& 5& 4& 2& 2& 2& 2& 2\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 284& 7& 3& 2& 2& 2& 2& 2& 2& 2\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 617& 32& 6& 4& 6& 2& 2& 2& 2& 2\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 471& 43& 13& 9& 2& 2& 2& 2& 2& 2 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 309& 107& 8& 2& 2& 2& 2& 2& 2& 2 \\[0.1cm]



KPath with one pass heursitic + corrected nk space + with duplicates
CU   & 49    & 107 &   2.18 & 6 & 5& 2& 2& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 21 & 16& 9& 7& 5& 4& 3& 3& 2& 2 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 43 & 14& 7& 4& 4& 3& 3& 3& 1& 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 221 &35& 19& 12& 9& 4& 6& 3& 3& 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 38& 9& 2& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 231& 13& 4& 3& 2& 1& 1& 1& 1& 1\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 853& 22& 9& 6& 5& 4 &4& 3& 3& 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 831& 35& 15& 11& 6& 5& 4& 5& 3& 3 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 294& 67& 18& 4& 3& 3& 1& 1& 1& 1\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 278& 7& 2& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 603& 28& 6& 5& 2& 2& 1& 1& 1& 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 453& 47&14& 6& 5& 1& 1& 1& 1& 1 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 322& 100& 7& 4& 1& 1& 1& 1& 1& 1 \\[0.1cm]





KPath with one pass heursitic + corrected n(k+1) to n(k) space +with no duplicates
CU   & 49    & 107 &   2.18 & 5 & 2& 2& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 17 & 10& 7& 5& 4& 3& 3& 2& 2& 2 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 33 &8& 4& 3& 3& 3& 3& 1& 1& 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 190 &19& 13& 8& 4& 8& 3& 3& 2& 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 37& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 195& 4& 3& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 692& 10& 6& 5& 4& 4 &3& 3& 3& 2\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 571& 23& 12& 9& 5& 6& 4& 11& 3& 3 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 229& 26& 4& 3& 3& 1& 1& 1& 1& 1\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 214& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 475& 7& 5& 2& 2& 1& 1& 1& 1& 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 369& 11& 6& 5& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 246& 7& 4& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]




KPath with one pass heursitic + corrected n(k+1) to n(k) space +with no duplicates + optimal_k heuristic
CU   & 49    & 107 &   2.18 & 3 & 2& 2& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 5 & 4& 3& 3& 2& 2& 2& 2& 2& 2 \\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 4 &3& 3& 2& 2& 2& 2& 1& 1& 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 5 &4& 3& 3& 2& 2& 2& 2& 2& 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 3& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 3& 2& 2& 2& 1& 1& 1& 1& 1& 1\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 6& 4& 3& 3& 3& 3 &2& 2& 2& 2\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 5& 4& 4& 4& 3& 3& 3& 2& 2& 2 \\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 4& 3& 3& 2& 2& 1& 1& 1& 1& 1\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 3& 2& 2& 1& 1& 1& 1& 1& 1& 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 4& 2& 2& 2& 2& 1& 1& 1& 1& 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 4& 3& 3& 3& 1& 1& 1& 1& 1& 1 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 & 4& 3& 2& 1& 1& 1& 1& 1& 1& 1 \\[0.1cm]




KLev Corrected ones
CU   & 49    & 107 &   2.18 & 3& 3& 3& 3& 3& 3& 3& 3& 3& 2\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 2& 2& 2& 2& 2& 2& 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 4 &4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4 \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 3& 3& 3& 3& 3& 3& 3& 3& 3& 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 4& 4& 4& 4& 4& 4& 4& 4& 4& 4\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 5& 5& 5& 5& 5& 5& 5& 5& 6& 5\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 3& 3& 3& 3& 3& 3& 3& 3& 3& 3\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 5 &5& 5& 5& 5& 5& 5& 5& 5& 5\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 4& 4& 4& 4& 4& 4& 4& 5& 5& 5 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 &  5& 5& 5& 5& 5& 5& 5& 5& 5& 5\\[0.1cm]



KLev with new code having new criteria - heursitic of utilizing overall nk space
CU   & 49    & 107 &   2.18 & 3& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & \fbox{15} & \fbox{8} & \fbox{5} & \fbox{4} & \fbox{3} & \fbox{3} & 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & \fbox{7} &4& \gbox{3}& \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & \fbox{11} & \fbox{6} & 4& \gbox{3} & \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2}\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & \gbox{3} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 4& \gbox{2}& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& \fbox{22} & \fbox{11} & \fbox{8} & \fbox{6} & \fbox{5} & \fbox{4} & \fbox{4} & 3& 3& 3\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& \fbox{22} & \fbox{12} & \fbox{8} & \fbox{6} & \fbox{5} & 4& 4& \gbox{3} & \gbox{3}& \gbox{3}\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 5& \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 3& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 5 &\gbox{3}& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}&\gbox{1}& \gbox{1}& \gbox{1} & \gbox{1}\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 4& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1} \\[0.1cm]
          Amazon   & 355K    & 926K &   2.76 &  \gbox{3}& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]



KLev with  new code having new criteria - heursitic of utilizing overall nk space and also added heursitic of heursitic of marked unmarked as well
CU   & 49    & 107 &   2.18 & \gbox{2}& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 2 & 2 & 2 & 2 & 2 & 2 & 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & \gbox{3} &\gbox{3}& \gbox{3}& \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 4 & 4 & \gbox{3} & \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2}\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & \gbox{3} & \gbox{2}& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 3 & 3 & 3 & 3 & 3 & 3 & 3 & \gbox{2} & \gbox{2} & \gbox{2} \\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 4 & \gbox{3} & 4 & \gbox{3} & \gbox{3} & \gbox{3}& \gbox{3} & \gbox{3} & \gbox{3}& \gbox{3}\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & \gbox{4} & \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & \gbox{2}& \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & \gbox{4} &\gbox{3}& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}&\gbox{1}& \gbox{1}& \gbox{1} & \gbox{1}\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & \gbox{3}& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1} \\[0.1cm]
          Amazon   & 355K    & 926K &   2.76 &  \gbox{3}& \gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]



KLev with  new code having new criteria - heursitic of utilizing overall nk space and also added heursitic of heursitic of marked unmarked as well+ heursitic of top path klev
CU   & 49    & 107 &   2.18 & \gbox{1}& \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 2 & 2 & 2 & 2 & 2 & 2 & 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & \gbox{3} &\gbox{3}& \gbox{2}& \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 4 & 4 & \gbox{3} & \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2}\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & \gbox{3} & \gbox{2}& \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 3 & 3 & 3 & 3 & 3 & 3 & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{2} \\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 4 & 4 & 4 & \gbox{3} & \gbox{3} & \gbox{3}& \gbox{3} & \gbox{3} & \gbox{3}& \gbox{3}\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & \gbox{4} & \gbox{3} & \gbox{2} & \gbox{2} & \gbox{2} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} \\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & \gbox{2}& \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1} & \gbox{1}\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & \gbox{4} &\gbox{2}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}&\gbox{1}& \gbox{1}& \gbox{1} & \gbox{1}\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & \gbox{3}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1} \\[0.1cm]
          Amazon   & 355K    & 926K &   2.76 &  \gbox{3}& \gbox{2}& \gbox{2}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}& \gbox{1}\\[0.1cm]




KLev with  new code having new criteria - improvements because of top path klev heursitic
CU   & 49    & 107 &   2.18 & \gbox{1}& \gbox{1} & 1 & 1& 1 & 1 & 1& 1& 1& 1\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 2 & 2 & 2 & 2 & 2 & 2 & 2& 2& 2& 2\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 & 3 & 3& \gbox{2} & 2 & 2 & 2 & \gbox{1} & 1 & 1 & 1 \\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 4 & 4 & 3 & 3 & 2 & 2 & 2 & 2 & 2 & 2\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 2 & \gbox{1} & 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1 \\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 & 3 & 2& \gbox{1} & 1 & 1 & 1 & 1 & 1 & 1 & 1 \\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 3 & 3 & 3 & 3 & 3 & 3 & \gbox{2} & 2 & 2 & 2 \\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 4 & 4 & 4 & 3 & 3 & 3& 3 & 3 & 3& 3\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 4 & 3 & 2 & 2 & 2 & \gbox{1} & 1 & 1 & 1 & 1 \\[0.1cm]
     Douban   & 155K    & 327K &   2.11 & 2& \gbox{1} & 1 & 1 & 1 & 1 & 1 & 1 & 1 & 1\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 4 &\gbox{2}& 2& 2& \gbox{1}& 1&1& 1& 1 & 1\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 & 3& 2& 2& \gbox{1}& 1& 1& 1& 1& 1& 1 \\[0.1cm]
          Amazon   & 355K    & 926K &   2.76 &  3& 2& 2& \gbox{1}& 1& 1& 1& 1& 1& 1\\[0.1cm]


kpath_plot_data.txt -> k table7 table8 table9

klev_plot_data.txt -> k prev_sbz table10 table11 table12 table13


Corrected version of table: Only Including KPath and KLev


-> Dataset & n  & m & m/n & Simp & Imprv & KPath - n & 2n & 5n & 10n & KLev - n & 2n & 5n & 10n \\
     CU   & 49    & 107 &   2.18 & 23 & 32&  5 & 4& 2&  2 & 3 & 3 & 3 & 3\\[0.1cm]
     AJazz   & 198    & 2.74K &   13.85 & 53&154& 19 & 16& 5& 3& 3& 3& 3& 3\\[0.1cm]
     HM   & 2.43K    & 16.6K &   6.86 &1.31K&753& 47 & 13& 5& 2& 4& 4& 4& 4\\[0.1cm]
     ArxAP   & 18.8K    & 198K &   10.55 & 9.36K& 6.49K &231 & 33& 10& 3& 5& 5& 5& 5\\[0.1cm]
     AsCaida   & 26.5K    & 53.4K &   2.02 & 24.7K& 979 &43 & 8& 2& 2& 4& 4& 4& 4\\[0.1cm]
     BrightK   & 58.2K    & 214K &   3.68 &  43.3K &10.3K & 242 & 14& 2& 2& 5& 5& 5& 5\\[0.1cm]
     LMocha   & 104K    & 2.19M &   21.07& 66.4K & 40K&  850 & 22& 6& 3& 4& 4& 4& 4\\[0.1cm]
     FlickrE   & 106K    & 2.32M &   21.87& 55K &51.7K& 737 & 43& 7& 4& 5& 5& 5& 5\\[0.1cm]
     WordNet   & 146K    & 657K &   4.50 & 96.9K & 23.7K& 303 & 66& 4& 2& 6& 6& 6& 6\\[0.1cm]
     Douban   & 155K    & 327K &   2.11 &  145K & 11.5K & 284& 7& 2& 2& 4& 4& 4& 4\\[0.1cm]
     Gowalla   & 197K    & 950K &   4.83 & 134K & 45.3K & 617 &32& 6& 2& 6& 6& 6& 6\\[0.1cm]
     Dblp   & 317K    & 1.05M &   3.31 &  214K & 42.3K &471 & 43& 2& 2& 6& 6& 6& 6 \\[0.1cm]
     Amazon   & 355K    & 926K &   2.76 &  204K & 80.1K & 309 & 107& 2& 2& 6& 6& 6& 6 \\[0.1cm]




 ./real_plot.sh ./output/real/CU/ CU 49 107
./real_plot.sh ./output/real/AJazz/ AJazz 198 2.74K
./real_plot.sh ./output/real/HM/ HM 2.43K 16.6K
./real_plot.sh ./output/real/ArxAP/ ArxAP 18.8K 198K
./real_plot.sh ./output/real/AsCaida/ AsCaida 26.5K 53.4K
./real_plot.sh ./output/real/BrightK/ BrightK 58.2K 214K
./real_plot.sh ./output/real/LMocha/ LMocha 104K 2.19M
./real_plot.sh ./output/real/FlickrE/ FlickrE 106K 2.32M
./real_plot.sh ./output/real/WordNet/ WordNet 146K 657K
./real_plot.sh ./output/real/Douban/ Douban 155K 327K
./real_plot.sh ./output/real/Gowalla/ Gowalla 197K 950K
./real_plot.sh ./output/real/Dblp/ Dblp 317K 1.05M
./real_plot.sh ./output/real/Amazon/ Amazon 355K 926K




unset key
unset label
set size 0.6,0.7
set origin 0.3,0.2


set xtics 0,1
set yrange [0:20]
set ytics 0,2
set xlabel ""
set ylabel ""

#plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'B1' with linespoints, \
#    "".location."kpath_plot_data.txt" using 1:(column(3)) title 'B1+H1' with linespoints,\
#    "".location."kpath_plot_data.txt" using 1:(column(4)) title 'B1+H1+H2' with linespoints,

plot "".location."kpath_plot_data.txt" using 1:(column(2)) title 'KPathOld' with linespoints, \
    "".location."kpath_plot_data.txt" using 1:(column(4))  title 'KPathNew' with linespoints lc rgb "blue",