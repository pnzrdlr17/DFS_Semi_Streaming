
./dataGen.sh 1 49 107 ./input/CU/download.tsv.contiguous-usa/contiguous-usa/out.contiguous-usa ./output/real/CU
echo "CU done"

./dataGen.sh 1 198 2742 ./input/AJazz/download.tsv.arenas-jazz/arenas-jazz/out.arenas-jazz  ./output/real/AJazz
echo "AJazz done"

./dataGen.sh 1 2426 16631 ./input/HM/download.tsv.petster-hamster/petster-hamster/out.petster-hamster  ./output/real/HM
echo "HM done"

./dataGen.sh 1 18771 198050 ./input/ArxAP/download.tsv.ca-AstroPh/ca-AstroPh/out.ca-AstroPh  ./output/real/ArxAP
echo "ArxAP done"

./dataGen.sh 1 26475 53381 ./input/AsCaida/download.tsv.as-caida20071105/as-caida20071105/out.as-caida20071105 ./output/real/AsCaida
echo "AsCaida done"

./dataGen.sh 1 58228 214078 ./input/BrightK/download.tsv.loc-brightkite_edges/loc-brightkite_edges/out.loc-brightkite_edges ./output/real/BrightK
echo "BrightK done"

./dataGen.sh 1 104103 2193083 ./input/LMocha/download.tsv.livemocha/livemocha/out.livemocha ./output/real/LMocha
echo "LMocha done"

./dataGen.sh 1 105938 2316948 ./input/FlickrE/download.tsv.flickrEdges/flickrEdges/out.flickrEdges ./output/real/FlickrE
echo "FlickrE done"

./dataGen.sh 1 146005 656999 ./input/WordNet/download.tsv.wordnet-words/wordnet-words/out.wordnet-words ./output/real/WordNet
echo "WordNet done"

./dataGen.sh 1 154908 327162 ./input/Douban/download.tsv.douban/douban/out.douban ./output/real/Douban
echo "Douban done"

./dataGen.sh 1 196591 950327 ./input/Gowalla/download.tsv.loc-gowalla_edges/loc-gowalla_edges/out.loc-gowalla_edges ./output/real/Gowalla
echo "Gowalla done"

./dataGen.sh 1 317080 1049866 ./input/Dblp/download.tsv.com-dblp/com-dblp/out.com-dblp ./output/real/Dblp
echo "Dblp done"

./dataGen.sh 1 334863 925872 ./input/Amazon/download.tsv.com-amazon/com-amazon/out.com-amazon  ./output/real/Amazon
echo "Amazon done"

echo "All real graphs done"





